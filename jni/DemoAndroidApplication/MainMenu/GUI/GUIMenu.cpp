#include "GUIMenu.hpp"

using namespace MPACK;
using namespace MPACK::Core;
using namespace MPACK::Math;
using namespace MPACK::Graphics;

GUIMenu::GUIMenu()
	: action(0), m_sprite(NULL)
{
	m_pMMInputController=new MMInputController();

	m_pMMInputController->Link_FDOWN(Param2PtrCallbackStruct(GUIMenu::DOWNEvent,this));
	m_pMMInputController->Link_FUP(Param2PtrCallbackStruct(GUIMenu::UPEvent,this));
}

GUIMenu::~GUIMenu()
{
	for(vector<GUIMenuButton*>::iterator it=m_button.begin();it!=m_button.end();++it)
	{
		delete (*it);
	}

	delete m_pMMInputController;
}

int GUIMenu::Update(GLfloat timeStep)
{
	m_pMMInputController->Update(timeStep);

	for(vector<GUIMenuButton*>::iterator it=m_button.begin();it!=m_button.end();++it)
	{
		if((*it)->m_pFinger)
		{
			(*it)->m_pos.x=(*it)->m_fixedPos.x+((*it)->m_pFinger->m_pos.x-(*it)->m_fingerStartPos.x);
		}
	}

	if(action)
	{
		LOGE("action = %d",action);
	}

	int i = action;
	action = 0;
	return i;
}

void GUIMenu::Render()
{
	GLfloat width=m_sprite->GetWidth()*0.5;
	GLfloat height=m_sprite->GetHeight()*0.5;
	GLfloat DX[4];
	DX[0]=-width;
	DX[1]=+width;
	DX[2]=+width;
	DX[3]=-width;
	GLfloat DY[4];
	DY[0]=-height;
	DY[1]=-height;
	DY[2]=+height;
	DY[3]=+height;

	for(vector<GUIMenuButton*>::iterator it=m_button.begin();it!=m_button.end();++it)
	{
		m_sprite->m_position=(*it)->m_pos;
		for(register int i=0;i<4;++i)
		{
			Vector2f pos=m_sprite->m_position;
			pos.x+=DX[i];
			pos.y+=DY[i];

			Vector3f color;

			AABB1Df mid((*it)->m_fixedPos.x-m_sprite->GetWidth()*0.5,(*it)->m_fixedPos.x+m_sprite->GetWidth()*0.5);

			if(mid.Contain(pos.x))
			{
				color=Vector3f(1.0f,1.0f,1.0f);
			}
			else
			{
				GLfloat factor;
				if(pos.x<mid.m_xmin)
				{
					factor=mid.m_xmin-pos.x;
				}
				else
				{
					factor=pos.x-mid.m_xmax;
				}
				factor/=mid.m_xmin;

				Vector3f lrColor(173.0f/255.0f,113.0f/255.0f,52.0f/255.0f);
				Vector3f midColor(1.0f,1.0f,1.0f);
				factor=1.0f-factor;
				//factor=factor*factor;
				color=midColor*factor+lrColor*(1.0f-factor);
			}

			m_sprite->m_color[i].x=min(1.0f,color.x);
			m_sprite->m_color[i].y=min(1.0f,color.y);
			m_sprite->m_color[i].z=min(1.0f,color.z);
		}
		m_sprite->Render();
	}

	for(vector<GUIMenuButton*>::iterator it=m_button.begin();it!=m_button.end();++it)
	{
		Vector2f &pos=(*it)->m_pos;
		Global::pFont->SendString((*it)->m_text,pos.x,pos.y,TextureMappedFont::ALIGN_CENTER);
	}
}

void GUIMenu::AddButton(string text, int id)
{
	GUIMenuButton* pButton=new GUIMenuButton;
	pButton->m_text=text;
	pButton->m_id=id;

	m_button.push_back(pButton);
}

void GUIMenu::BuildLayout()
{
	const GLfloat TOP_PIXELS=75.0f;
	const GLfloat BOTTOM_PIXELS=20.0f;
	const GLfloat SPACING_PIXELS=20.0f;

	GLfloat buttons=m_button.size();
	GLfloat buttonWidth=0.40*Render::GetScreenWidth();
	GLfloat buttonHeight=(Render::GetScreenHeight()-TOP_PIXELS-BOTTOM_PIXELS-(buttons-1.0f)*SPACING_PIXELS)/buttons;

	m_sprite->SetSize(buttonWidth,buttonHeight);

	GLfloat indexButton=1.0f;
	for(vector<GUIMenuButton*>::iterator it=m_button.begin();it!=m_button.end();++it)
	{
		GLfloat x=Render::GetScreenWidth()*0.5f;
		GLfloat y=TOP_PIXELS+buttonHeight*(indexButton-0.5)+SPACING_PIXELS*(indexButton-1.0f);
		//y=Render::GetScreenHeight()-y;
		(*it)->m_fixedPos=(*it)->m_pos=Vector2f(x,y);
		indexButton+=1.0f;
	}
}

void GUIMenu::DOWNEvent(void *pointer1, void *pointer2)
{
	GUIMenu *pGUI=(GUIMenu*)(pointer1);
	MPACK::Input::Finger *pFinger=(MPACK::Input::Finger*)(pointer2);
	for(vector<GUIMenuButton*>::iterator it=pGUI->m_button.begin();it!=pGUI->m_button.end();++it)
	{
		if((*it)->m_pFinger)
		{
			continue;
		}

		Vector2f &pos=(*it)->m_pos;
		AABB2Df A;
		GLfloat width=pGUI->m_sprite->GetWidth()*0.5f;
		GLfloat height=pGUI->m_sprite->GetHeight()*0.5f;
		A.m_xmin=pos.x-width;
		A.m_xmax=pos.x+width;
		A.m_ymin=pos.y-height;
		A.m_ymax=pos.y+height;
		if(A.Contain(pFinger->m_pos))
		{
			(*it)->m_pFinger=pFinger;
			(*it)->m_fingerStartPos=pFinger->m_pos;
			break;
		}
	}
}

void GUIMenu::UPEvent(void *pointer1, void *pointer2)
{
	const GLfloat ACTION_THRESHOLD=0.1f;
	GLfloat leftThreshold=Render::GetScreenWidth()*ACTION_THRESHOLD;
	GLfloat rightThreshold=Render::GetScreenWidth()*(1.0f-ACTION_THRESHOLD);

	GUIMenu *pGUI=(GUIMenu*)(pointer1);
	MPACK::Input::Finger *pFinger=(MPACK::Input::Finger*)(pointer2);
	for(vector<GUIMenuButton*>::iterator it=pGUI->m_button.begin();it!=pGUI->m_button.end();++it)
	{
		if((*it)->m_pFinger==pFinger)
		{
			(*it)->m_pFinger=NULL;

			if((*it)->m_pos.x<leftThreshold || (*it)->m_pos.x>rightThreshold)
			{
				pGUI->action=(*it)->m_id;
			}
			(*it)->m_pos=(*it)->m_fixedPos;
		}
	}
}

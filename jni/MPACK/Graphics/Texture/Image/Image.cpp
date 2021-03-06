#include "Image.hpp"

#include "Math.hpp"
#include "Misc.hpp"
#include "StringEx.hpp"
#include "TargaImage.hpp"
#include "PNGImage.hpp"

using namespace std;
using namespace MPACK::Core;

namespace MPACK
{
	namespace Graphics
	{
		SeamCarvingEdit::SeamCarvingEdit(int x, int y, double add, double multiply)
			: pixel(x, y), add(add), multiply(multiply)
		{
		}

		Image::Image()
			: m_width(0), m_height(0), m_GLFormatType(0), m_bytesPerPixel(0),
			  m_imageBuffer(NULL), m_internalFormatType(Image::InternalFormatType::NONE)
		{
		}

		Image::~Image()
		{
			Unload();
		}

		void Image::Init(const int &width, const int &height, const bool grayscale)
		{
			Unload();

			if (width < 0)
			{
				LOGW("PNGImage::Init() invalid width!");
				m_width = 1;
			}
			else
			{
				m_width = width;
			}

			if (height < 0)
			{
				LOGW("PNGImage::Init() invalid height!");
				m_height = 1;
			}
			else
			{
				m_height = height;
			}

			if (grayscale)
			{
				m_bytesPerPixel = 1;
				m_GLFormatType = GL_LUMINANCE;
				m_internalFormatType = InternalFormatType::GRAY;
			}
			else
			{
				m_bytesPerPixel = 4;
				m_GLFormatType = GL_RGBA;
				m_internalFormatType = InternalFormatType::RGBA;
			}
			m_imageBuffer = new BYTE[m_width * m_height * m_bytesPerPixel];
		}

		ReturnValue Image::Load(const std::string& path, bool flipForOpenGL, FileFormatType fileFormatType)
		{
			Unload();

			if (fileFormatType == FileFormatType::AUTO)
			{
				string ext;
				Core::StringEx::GetExtension(path.c_str(), ext);
				Core::StringEx::Upper(ext);
				if(ext == "TGA")
				{
					fileFormatType = FileFormatType::TGA;
				}
				else if(ext == "PNG")
				{
					fileFormatType = FileFormatType::PNG;
				}
				else if(ext == "PPM")
				{
					fileFormatType = FileFormatType::PPM;
				}
				else
				{
					LOGE("Image::Load() format auto-detect fail: invalid extension: %s", path.c_str());
					return RETURN_VALUE_KO;
				}
			}

			switch(fileFormatType)
			{
				case FileFormatType::TGA:
					if (LoadTGA(this, path, flipForOpenGL) == RETURN_VALUE_KO)
					{
						LOGE("Image::Load() fail to load TGA image: %s", path.c_str());
						return RETURN_VALUE_KO;
					}
				break;
				case FileFormatType::PNG:
					if (LoadPNG(this, path, flipForOpenGL) == RETURN_VALUE_KO)
					{
						LOGE("Image::Load() fail to load PNG image: %s", path.c_str());
						return RETURN_VALUE_KO;
					}
				break;
				case FileFormatType::PPM:
					if (LoadPPM(this, path, flipForOpenGL) == RETURN_VALUE_KO)
					{
						LOGE("Image::Load() fail to load PPM image: %s", path.c_str());
						return RETURN_VALUE_KO;
					}
				break;
				default:
				break;
			}

			return RETURN_VALUE_OK;
		}

		ReturnValue Image::Save(const std::string& path, FileFormatType fileFormatType)
		{
			if (fileFormatType == FileFormatType::AUTO)
			{
				fileFormatType = FileFormatType::PNG;
			}

			switch(fileFormatType)
			{
				case FileFormatType::TGA:
					if (SaveTGA(this, path) == RETURN_VALUE_KO)
					{
						LOGE("Image::Save() fail to save image as TGA");
						return RETURN_VALUE_KO;
					}
				break;
				case FileFormatType::PNG:
					if (SavePNG(this, path) == RETURN_VALUE_KO)
					{
						LOGE("Image::Save() fail to save image as PNG");
						return RETURN_VALUE_KO;
					}
				break;
				case FileFormatType::PPM:
					if (SavePPM(this, path) == RETURN_VALUE_KO)
					{
						LOGE("Image::Save() fail to save image as PPM");
						return RETURN_VALUE_KO;
					}
				break;
				default:
				break;
			}
			return RETURN_VALUE_OK;
		}

		void Image::Unload()
		{
			if (m_imageBuffer)
			{
				m_width = 0;
				m_height = 0;
				m_internalFormatType = InternalFormatType::NONE;
				m_GLFormatType = 0;
				m_bytesPerPixel = 0;
				delete[] m_imageBuffer;
				m_imageBuffer = 0;
			}
		}

		void Image::InitColor(const int &width, const int &height, const Color &c)
		{
			Init(width, height);
			FillColor(Rect(0, 0, m_width, m_height), c);
		}

		void Image::FillColor(const Rect &rect, const Color &c)
		{
			for(int i = 0; i < m_width; ++i)
			{
				for(int j = 0; j < m_height; ++j)
				{
					SetPixel(rect.x + i, rect.y + j, c);
				}
			}
		}

		void Image::Blit(Image *image, const GLushort &x, const GLushort &y)
		{
			BlitSafe(image, Point(x,y), Rect(0,0,image->GetWidth(),image->GetHeight()));
		}

		void Image::Blit(Image *image, const Point &point)
		{
			BlitSafe(image, point, Rect(0,0,image->GetWidth(),image->GetHeight()));
		}

		void Image::Blit(Image *image, const Point &point, const Rect &rect)
		{
			BlitSafe(image, point, rect);
		}

		void Image::FlipVertical()
		{
			for(int i = 0; i < m_width; ++i)
			{
				for(int j = 0; j < (m_height >> 1); ++j)
				{
					int offset1 = j * m_width + i;
					offset1 *= m_bytesPerPixel;

					int vi = i;
					int vj = m_height - j - 1;

					int offset2 = vj * m_width + vi;
					offset2 *= m_bytesPerPixel;

					StringEx::MemSwap((char*)(m_imageBuffer + offset1),(char*)(m_imageBuffer + offset2), m_bytesPerPixel);
				}
			}
		}

		void Image::FlipHorizontal()
		{
			for(int i = 0; i < (m_width >> 1); ++i)
			{
				for(int j = 0; j < m_height; ++j)
				{
					int offset1 = j * m_width + i;
					offset1 *= m_bytesPerPixel;

					int vi = m_width - i - 1;
					int vj = j;

					int offset2 = vj * m_width + vi;
					offset2 *= m_bytesPerPixel;

					StringEx::MemSwap((char*)(m_imageBuffer + offset1), (char*)(m_imageBuffer + offset2), m_bytesPerPixel);
				}
			}
		}

		Image* Image::Clone()
		{
			Image *img = new Image;
			if (m_bytesPerPixel == 1) {
				img->Init(this->GetWidth(), this->GetHeight(), true);
			} else {
				img->Init(this->GetWidth(), this->GetHeight());
			}
			img->Blit(this, 0, 0);
			return img;
		}

		Image* Image::Grayscale()
		{
			Image *img = new Image();
			img->Init(this->GetWidth(), this->GetHeight(), true);
			for(int i = 0; i < m_width; ++i)
			{
				for(int j = 0; j < m_height; ++j)
				{
					img->SetPixel(i, j, GetPixel(i, j));
				}
			}
			return img;
		}

		Image* Image::Sobel()
		{
			double kernelX[3][3] = {{-1, 0, 1},
                       {-2, 0, 2},
                       {-1, 0, 1}};

		  double kernelY[3][3] = {{-1, -2, -1},
                       {0,  0,  0},
                       {1,  2,  1}};

			Image *grayscale = this->Grayscale();
			Image *img = grayscale->Clone();

			for (int i = 0; i < grayscale->m_width; ++i)
			{
					for (int j = 0; j < grayscale->m_height; ++j)
					{
						double magX = 0.0;
						double magY = 0.0;
						for(int a = 0; a < 3; a++)
						{
						    for(int b = 0; b < 3; b++)
						    {
						        int xn = i + a - 1;
						        int yn = j + b - 1;

						        magX += (double)(grayscale->GetPixel(xn, yn).r) * kernelX[a][b];
										magY += (double)(grayscale->GetPixel(xn, yn).r) * kernelY[a][b];
						    }
						 }
						 double mag = Math::Misc<double>::Abs(magX) + Math::Misc<double>::Abs(magY);
						 //double mag = Math::Misc<double>::Sqrt(magX * magX + magY * magY);
						 img->SetPixel(i, j, Color(mag, mag, mag));
					}
			}
			delete grayscale;
			return img;
		}

		void Image::SeamCarvingAddRectangleEnergyModifier(std::vector<SeamCarvingEdit> *energyModifiers, int x, int y, int xSize, int ySize, double add, double multiply)
		{
			for (int i = 0; i < xSize; ++i)
			{
				for (int j = 0; j < ySize; ++j)
				{
					energyModifiers->push_back(SeamCarvingEdit(x + i, y + j, add, multiply));
				}
			}
		}

		void Image::SeamCarvingVerticalExtendSeam(int *dest, int *src, int height)
		{
			for (int j = 0; j < height; ++j)
			{
				if (dest[j] > src[j])
				{
					++dest[j];
				}
			}
		}

		Image* Image::SeamCarvingAddVertical(int *seam, Image *img)
		{
			Image *result = new Image();
			result->Init(img->GetWidth() + 1, img->GetHeight());
			for (int j = 0; j < img->GetHeight(); ++j)
			{
				int currentI = 0;
				for (int i = 0; i < img->GetWidth(); ++i)
				{
					if (seam[j] != i)
					{
						result->SetPixel(currentI, j, img->GetPixel(i, j));
					}
					else if (seam[j] == i)
					{
						Color color = img->GetPixel(i, j);
						result->SetPixel(currentI, j, color);
						++currentI;
						Color colorL = img->GetPixel(i - 1, j);
						Color colorR = img->GetPixel(i + 1, j);
						color.r = ((double)(colorL.r) + (double)(color.r) + (double)(colorR.r))/3.0;
						color.g = ((double)(colorL.g) + (double)(color.g) + (double)(colorR.g))/3.0;
						color.b = ((double)(colorL.b) + (double)(color.b) + (double)(colorR.b))/3.0;
						color.a = ((double)(colorL.a) + (double)(color.a) + (double)(colorR.a))/3.0;
						result->SetPixel(currentI, j, color);
					}
					++currentI;
				}
			}
			return result;
		}

		void Image::ApplyVerticalSeamOnEnergyModifiers(std::vector<SeamCarvingEdit> *energyModifiers, int *seam, int height)
		{
			vector<SeamCarvingEdit> tmp;
			for (vector<SeamCarvingEdit>::iterator it = energyModifiers->begin(); it != energyModifiers->end(); ++it)
			{
				if (seam[it->pixel.y] < it->pixel.x)
				{
					--it->pixel.x;
					tmp.push_back(*it);
				}
				else if (seam[it->pixel.y] != it->pixel.x)
				{
					tmp.push_back(*it);
				}
			}
			*energyModifiers = tmp;
		}

		void Image::SeamCarvingApplyEnergyModifiers(double *energyMap, int width, int height, vector<SeamCarvingEdit> *energyModifiers)
		{
			for (vector<SeamCarvingEdit>::iterator it = energyModifiers->begin(); it != energyModifiers->end(); ++it)
			{
				int offset = it->pixel.x * height + it->pixel.y;
				energyMap[offset] = energyMap[offset] * it->multiply + it->add;
			}
		}

		void Image::RotateEnergyModifiersClockwise(std::vector<SeamCarvingEdit> *energyModifiers, int width, int height)
		{
			for (vector<SeamCarvingEdit>::iterator it = energyModifiers->begin(); it != energyModifiers->end(); ++it)
			{
				Point pixel;
				pixel.x = it->pixel.y;
				pixel.y = height - it->pixel.x - 1;
				it->pixel = pixel;
			}
		}

		void Image::RotateEnergyModifiersCounterClockwise(vector<SeamCarvingEdit> *energyModifiers, int width, int height)
		{
			for (vector<SeamCarvingEdit>::iterator it = energyModifiers->begin(); it != energyModifiers->end(); ++it)
			{
				Point pixel;
				pixel.x = width - it->pixel.y + 1;
				pixel.y = it->pixel.x;
				it->pixel = pixel;
			}
		}

		int* Image::GetSeam(Image *img, SeamCarvingType type, vector<SeamCarvingEdit> *energyModifiers)
		{
			int *seam = new int[img->GetHeight()];

			if (type == Image::SeamCarvingType::BEST_PATH)
			{
				Image *energy = img->Sobel();
				double *energyMap = new double[img->GetWidth() * img->GetHeight()];
				double *dpBestEnergy = new double[img->GetWidth() * img->GetHeight()];
				int *dpBestPath = new int[img->GetWidth() * img->GetHeight()];
				for (int i = 0; i < energy->GetWidth(); ++i)
				{
					for (int j = 0; j < energy->GetHeight(); ++j)
					{
						int offset = i * energy->GetHeight() + j;
						energyMap[offset] = energy->GetPixel(i, j).r;
					}
				}
				delete energy;

				if (energyModifiers)
				{
					Image::SeamCarvingApplyEnergyModifiers(energyMap, img->GetWidth(), img->GetHeight(), energyModifiers);
				}

				for (int i = 0; i < img->GetWidth(); ++i)
				{
					int offset = i * img->GetHeight() + 0;
					dpBestEnergy[offset] = energyMap[offset];
					dpBestPath[offset] = 0;
				}
				for (int j = 1; j < img->GetHeight(); ++j)
				{
					for (int i = 0; i < img->GetWidth(); ++i)
					{
						int offset = i * img->GetHeight() + j;
						dpBestEnergy[offset] = dpBestEnergy[i * img->GetHeight() + j - 1];
						dpBestPath[offset] = 0;
						if (i > 0)
						{
							int offset2 = (i - 1) * img->GetHeight() + j - 1;
							if (dpBestEnergy[offset] > dpBestEnergy[offset2])
							{
								dpBestEnergy[offset] = dpBestEnergy[offset2];
								dpBestPath[offset] = -1;
							}
						}
						if (i < img->GetWidth() - 1)
						{
							int offset2 = (i + 1) * img->GetHeight() + j - 1;
							if (dpBestEnergy[offset] > dpBestEnergy[offset2])
							{
								dpBestEnergy[offset] = dpBestEnergy[offset2];
								dpBestPath[offset] = 1;
							}
						}
						dpBestEnergy[offset] += energyMap[offset];
					}
				}
				int bestX = 0, bestY = img->GetHeight() - 1;
				for (int i = 0; i < img->GetWidth(); ++i)
				{
					int bestOffset = bestX * img->GetHeight() + bestY;
					int offset = i * img->GetHeight() + img->GetHeight() - 1;
					if (dpBestEnergy[bestOffset] > dpBestEnergy[offset])
					{
						bestX = i;
						bestY = img->GetHeight() - 1;
					}
				}
				while (bestY >= 0)
				{
						seam[bestY] = bestX;
						int offset = bestX * img->GetHeight() + bestY;
						bestX += dpBestPath[offset];
						--bestY;
				}
				delete[] energyMap;
				delete[] dpBestEnergy;
				delete[] dpBestPath;
			}
			else if (type == Image::SeamCarvingType::RANDOM_PATH)
			{
				int x = Core::Random::Int(0, img->GetWidth() - 1);
				for (int y = 0; y < img->GetHeight(); ++y)
				{
						seam[y] = x;
						x += Core::Random::Int(-1, 1);
						x = Math::Misc<int>::Clamp(0, x, img->GetWidth() - 1);
				}
			}
			else if (type == Image::SeamCarvingType::GREEDY_PATH)
			{
				Image *energy = img->Sobel();
				double *energyMap = new double[energy->GetWidth() * energy->GetHeight()];
				double *dpBestEnergy = new double[img->GetWidth() * img->GetHeight()];

				for (int i = 0; i < energy->GetWidth(); ++i)
				{
					for (int j = 0; j < energy->GetHeight(); ++j)
					{
						int offset = i * energy->GetHeight() + j;
						energyMap[offset] = energy->GetPixel(i, j).r;
					}
				}
				delete energy;

				if (energyModifiers)
				{
					Image::SeamCarvingApplyEnergyModifiers(energyMap, img->GetWidth(), img->GetHeight(), energyModifiers);
				}

				int bestX = 0;
				for (int x = 0; x < img->GetWidth(); ++x)
				{
					int xOffset = x * img->GetHeight() + 0;
					int bestXOffset = bestX * img->GetHeight() + 0;
					if (energyMap[xOffset] < energyMap[bestXOffset])
					{
						bestX = x;
					}
				}
				int x = bestX;
				int offset = x * img->GetHeight() + 0;
				seam[0] = x;
				for (int y = 1; y < img->GetHeight(); ++y)
				{
					if (x > 0)
					{
						int xOffset = x * img->GetHeight() + y;
						int newOffset = (x - 1) * img->GetHeight() + y;
						if (energyMap[xOffset] > energyMap[newOffset])
						{
							x = x - 1;
						}
					}

					if (x < img->GetWidth() - 1)
					{
						int xOffset = x * img->GetHeight() + y;
						int newOffset = (x - 1) * img->GetHeight() + y;
						if (energyMap[xOffset] > energyMap[newOffset] )
						{
							x = x + 1;
						}
					}

					seam[y] = x;
				}
				delete[] energyMap;
				delete[] dpBestEnergy;
			}
			return seam;
		}

		Image* Image::SeamCarvingHorizontalDownsize(SeamCarvingType type, vector<SeamCarvingEdit> *energyModifiers)
		{
			int *seam = Image::GetSeam(this, type, energyModifiers);
			Image *img = new Image();
			img->Init(m_width - 1, m_height);
			for (int j = 0; j < m_height; ++j)
			{
				int currentI = 0;
				for (int i = 0; i < m_width; ++i)
				{
					if (seam[j] != i)
					{
						img->SetPixel(currentI, j, GetPixel(i, j));
						++currentI;
					}
				}
			}
			if (energyModifiers)
			{
				Image::ApplyVerticalSeamOnEnergyModifiers(energyModifiers, seam, m_height);
			}
			delete[] seam;
			return img;
		}

		Image* Image::SeamCarvingHorizontalDownsize(int downsize, SeamCarvingType type, vector<SeamCarvingEdit> *energyModifiers)
		{
			if (downsize <= 0)
			{
				return Clone();
			}
			if (downsize == 1)
			{
				return SeamCarvingHorizontalDownsize(type, energyModifiers);
			}
			Image *lastImg = SeamCarvingHorizontalDownsize(type, energyModifiers);
			for (int i = 1; i < downsize; ++i)
			{
				Image *img = lastImg->SeamCarvingHorizontalDownsize(type, energyModifiers);
				delete lastImg;
				lastImg = img;
			}
			return lastImg;
		}

		Image* Image::RotateClockwise()
		{
			Image *img = new Image();
			img->Init(m_height, m_width);
			for (int i = 0; i < img->m_width; ++i) {
				for (int j = 0; j < img->m_height; ++j) {
					img->SetPixel(i, j, GetPixel(j, m_height - i - 1));
				}
			}
			return img;
		}

		Image* Image::RotateCounterClockwise()
		{
			Image *img = new Image();
			img->Init(m_height, m_width);
			for (int i = 0; i < img->m_width; ++i) {
				for (int j = 0; j < img->m_height; ++j) {
					img->SetPixel(i, j, GetPixel(m_width - j - 1, i));
				}
			}
			return img;
		}

		Image* Image::SeamCarvingVerticalDownsize(SeamCarvingType type, vector<SeamCarvingEdit> *energyModifiers)
		{
			if (energyModifiers)
			{
				Image::RotateEnergyModifiersClockwise(energyModifiers, m_width, m_height);
			}
			Image *rotatedImg = RotateClockwise();
			Image *img = rotatedImg->SeamCarvingHorizontalDownsize(type, energyModifiers);
			delete rotatedImg;
			rotatedImg = img->RotateCounterClockwise();
			if (energyModifiers)
			{
				Image::RotateEnergyModifiersCounterClockwise(energyModifiers, img->m_width, img->m_height);
			}
			delete img;
			return rotatedImg;
		}

		Image* Image::SeamCarvingVerticalDownsize(int downsize, SeamCarvingType type, vector<SeamCarvingEdit> *energyModifiers)
		{
			if (energyModifiers)
			{
				Image::RotateEnergyModifiersClockwise(energyModifiers, m_width, m_height);
			}
			Image *rotatedImg = RotateClockwise();
			Image *img = rotatedImg->SeamCarvingHorizontalDownsize(downsize, type, energyModifiers);
			delete rotatedImg;
			rotatedImg = img->RotateCounterClockwise();
			if (energyModifiers)
			{
				Image::RotateEnergyModifiersCounterClockwise(energyModifiers, img->m_width, img->m_height);
			}
			delete img;
			return rotatedImg;
		}

		Image* Image::SeamCarvingDownsize(int horizontalDownsize, int verticalDownsize, SeamCarvingType type, vector<SeamCarvingEdit> *energyModifiers)
		{
			Image *horizontalDownsizeImg = SeamCarvingHorizontalDownsize(horizontalDownsize, type, energyModifiers);
			Image *verticalDownsizeImg = horizontalDownsizeImg->SeamCarvingVerticalDownsize(verticalDownsize, type, energyModifiers);
			delete horizontalDownsizeImg;
			return verticalDownsizeImg;
		}

		Image* Image::SeamCarvingHorizontalUpsize(int upsize, SeamCarvingType type, vector<SeamCarvingEdit> *energyModifiers)
		{
			if (upsize == 0)
			{
				return Clone();
			}
			vector<int*> seams;
			Image *lastImg = this;
			bool internalModifiers = false;
			if (!energyModifiers)
			{
				internalModifiers = true;
				energyModifiers = new vector<SeamCarvingEdit>;
			}
			for (int i = 0; i < upsize; ++i)
			{
				int *seam = Image::GetSeam(lastImg, type, energyModifiers);
				Image *img = new Image();
				img->Init(m_width - 1, m_height);
				for (int j = 0; j < m_height; ++j)
				{
					int currentI = 0;
					for (int i = 0; i < m_width; ++i)
					{
						if (seam[j] != i)
						{
							img->SetPixel(currentI, j, GetPixel(i, j));
							++currentI;
						}
						else
						{
							energyModifiers->push_back(SeamCarvingEdit(i, j, -100, -2));
						}
					}
				}
				if (energyModifiers)
				{
					Image::ApplyVerticalSeamOnEnergyModifiers(energyModifiers, seam, m_height);
				}
				if (lastImg != this)
				{
					delete lastImg;
				}
				lastImg = img;
				seams.push_back(seam);
			}
			if (internalModifiers) {
				delete energyModifiers;
			}

			for (int i = 0; i < (int)(seams.size()); ++i)
			{
					for (int j = 0; j < i; ++j)
					{
							Image::SeamCarvingVerticalExtendSeam(seams[j], seams[i], m_height);
					}
			}

			lastImg = this;
			for (int i = (int)(seams.size()); i > 0; --i)
			{
				int *seam = seams[i];
				Image *img = Image::SeamCarvingAddVertical(seam, lastImg);
				for (int j = 0; i < j; ++j)
				{
					Image::SeamCarvingVerticalExtendSeam(seams[j], seam, m_height);
				}
				if (lastImg != this)
				{
					delete lastImg;
				}
				lastImg = img;
			}
			return lastImg;
		}

		Image* Image::SeamCarvingVerticalUpsize(int upsize, SeamCarvingType type, vector<SeamCarvingEdit> *energyModifiers)
		{
			if (energyModifiers)
			{
				Image::RotateEnergyModifiersClockwise(energyModifiers, m_width, m_height);
			}
			Image *rotatedImg = RotateClockwise();
			Image *img = rotatedImg->SeamCarvingHorizontalUpsize(upsize, type, energyModifiers);
			delete rotatedImg;
			rotatedImg = img->RotateCounterClockwise();
			if (energyModifiers)
			{
				Image::RotateEnergyModifiersCounterClockwise(energyModifiers, img->m_width, img->m_height);
			}
			delete img;
			return rotatedImg;
		}

		Image* Image::SeamCarvingUpsize(int horizontalUpsize, int verticalUpsize, SeamCarvingType type, vector<SeamCarvingEdit> *energyModifiers)
		{
				Image *horizontalUpsizeImg = SeamCarvingHorizontalUpsize(horizontalUpsize, type, energyModifiers);
				Image *verticalUpsizeImg = horizontalUpsizeImg->SeamCarvingVerticalUpsize(verticalUpsize, type, energyModifiers);
				delete horizontalUpsizeImg;
				return verticalUpsizeImg;
		}

		GLushort Image::GetWidth() const
		{
			return m_width;
		}

		GLushort Image::GetHeight() const
		{
			return m_height;
		}

		GLushort Image::GetBytesPerPixel() const
		{
			return m_bytesPerPixel;
		}

		GLint Image::GetGLFormat() const
		{
			return m_GLFormatType;
		}

		Image::InternalFormatType Image::GetFormat() const
		{
			return m_internalFormatType;
		}

		bool Image::HaveAlphaChannel() const
		{
			return m_internalFormatType == Image::InternalFormatType::GRAY_ALPHA ||
				   m_internalFormatType == Image::InternalFormatType::RGBA;
		}

		const BYTE* Image::GetImageData() const
		{
			return m_imageBuffer;
		}

		const BYTE* Image::GetPixelPointer(const GLushort &x, const GLushort &y) const
		{
			int index = y * m_width + x;
			index *= m_bytesPerPixel;
			return m_imageBuffer + index;
		}

		Color Image::GetPixel(GLushort x, GLushort y) const
		{
			if (x < 0) {
				x = 0;
			}
			if (y < 0) {
				y = 0;
			}
			if (x >= m_width - 1) {
				x = m_width - 1;
			}
			if (y >= m_height - 1) {
				y = m_height - 1;
			}
			int index =  y * m_width + x;
			index *= m_bytesPerPixel;
			if (m_bytesPerPixel == 4)
			{
				return Color(m_imageBuffer[index], m_imageBuffer[index+1],
							 m_imageBuffer[index+2], m_imageBuffer[index+3]);
			}
			else if(m_bytesPerPixel == 3)
			{
				return Color(m_imageBuffer[index], m_imageBuffer[index+1],
							 m_imageBuffer[index+2], 255);
			}
			else if(m_bytesPerPixel == 2)
			{
				return Color(m_imageBuffer[index], m_imageBuffer[index],
							 m_imageBuffer[index], m_imageBuffer[index+1]);
			}
			else
			{
				return Color(m_imageBuffer[index], m_imageBuffer[index],
							 m_imageBuffer[index], 255);
			}
		}

		void Image::SetPixel(const GLushort &x, const GLushort &y, const Color &c)
		{
			int index = y * m_width + x;
			index *= m_bytesPerPixel;
			if (m_bytesPerPixel == 4)
			{
				m_imageBuffer[index] = c.r;
				m_imageBuffer[index+1] = c.g;
				m_imageBuffer[index+2] = c.b;
				m_imageBuffer[index+3] = c.a;
			}
			else if(m_bytesPerPixel == 3)
			{
				m_imageBuffer[index] = c.r;
				m_imageBuffer[index+1] = c.g;
				m_imageBuffer[index+2] = c.b;
			}
			else if(m_bytesPerPixel == 2)
			{
				unsigned char gray = (c.r + c.g + c.b) / 3;
				m_imageBuffer[index] = gray;
				m_imageBuffer[index+1] = c.a;
			}
			else
			{
				unsigned char gray = (c.r + c.g + c.b) / 3;
				m_imageBuffer[index] = gray;
			}
		}

		void Image::BlitSafe(Image *image, Point point, Rect rect)
		{
			GLushort width = image->GetWidth();
			GLushort height = image->GetHeight();

			if (point.x >= m_width || point.y >= m_height)
			{
				return;
			}

			if (rect.width <= 0 || rect.height <= 0)
			{
				return;
			}

			if (rect.x >= width || rect.y >= height)
			{
				return;
			}

			if (point.x < 0)
			{
				point.x = 0;
			}

			if (point.y < 0)
			{
				point.y = 0;
			}

			GLushort maxWidth = m_width - point.x;
			if (rect.width > maxWidth)
			{
				rect.width = maxWidth;
			}

			GLushort maxHeight = m_height - point.y;
			if (rect.height > maxHeight)
			{
				rect.height = maxHeight - point.y;
			}

			for (int i = 0; i < rect.width; ++i)
			{
				for (int j = 0; j < rect.height; ++j)
				{
					SetPixel(point.x + i,point.y + j, image->GetPixel(rect.x + i, rect.y + j));
				}
			}
		}

		GLushort GetBPP(GLint format)
		{
			switch(format)
			{
				case GL_RGB:
					return 3;
				break;
				case GL_RGBA:
					return 4;
				break;
				case GL_LUMINANCE:
					return 1;
				break;
				case GL_LUMINANCE_ALPHA:
					return 2;
				break;
			}
			return 0;
		}
	}
}

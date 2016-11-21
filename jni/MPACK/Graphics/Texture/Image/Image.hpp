#ifndef MPACK_IMAGE_HPP
#define MPACK_IMAGE_HPP

#include "Types.hpp"

#include "Color.hpp"
#include "Rect.hpp"

namespace MPACK
{
	namespace Graphics
	{
		typedef MPACK::Math::Vector2<int> Point;

		class SeamCarvingEdit
		{
		public:
			SeamCarvingEdit(int x, int y, double add, double multiply = 1.0);

			Point pixel;
			double add;
			double multiply;
		};

		class Image
		{
		public:
			enum InternalFormatType {NONE, GRAY, GRAY_ALPHA, RGB, RGBA};
			enum FileFormatType {AUTO, PNG, TGA, PPM};
			enum SeamCarvingType {RANDOM_PATH, GREEDY_PATH, BEST_PATH};

			Image();
			~Image();

			void Init(const int &width, const int &height, const bool grayscale = false);
			Core::ReturnValue Load(const std::string& path, bool flipForOpenGL = true, FileFormatType fileFormatType = AUTO);
			Core::ReturnValue Save(const std::string& path, FileFormatType fileFormatType = AUTO);
			void Unload();

			void InitColor(const int &width, const int &height, const Color &c);
			void FillColor(const Rect &rect, const Color &c);

			void Blit(Image *image, const GLushort &x, const GLushort &y);
			void Blit(Image *image, const Point &point);
			void Blit(Image *image, const Point &point, const Rect &rect);

			void FlipVertical();
			void FlipHorizontal();
			Image* Clone();

			Image* Grayscale();
			Image* Sobel();

			Image* SeamCarvingHorizontalDownsize(SeamCarvingType type = BEST_PATH, std::vector<SeamCarvingEdit> *energyModifiers = NULL);
			Image* SeamCarvingHorizontalDownsize(int downsize, SeamCarvingType type = BEST_PATH, std::vector<SeamCarvingEdit> *energyModifiers = NULL);

			Image* RotateClockwise();
			Image* RotateCounterClockwise();

			Image* SeamCarvingVerticalDownsize(SeamCarvingType type = BEST_PATH, std::vector<SeamCarvingEdit> *energyModifiers = NULL);
			Image* SeamCarvingVerticalDownsize(int downsize, SeamCarvingType type = BEST_PATH, std::vector<SeamCarvingEdit> *energyModifiers = NULL);

			Image* SeamCarvingDownsize(int horizontalDownsize, int verticalDownsize, SeamCarvingType type = BEST_PATH, std::vector<SeamCarvingEdit> *energyModifiers = NULL);

			Image* SeamCarvingHorizontalUpsize(int upsize, SeamCarvingType type = BEST_PATH, std::vector<SeamCarvingEdit> *energyModifiers = NULL);
			Image* SeamCarvingVerticalUpsize(int upsize, SeamCarvingType type = BEST_PATH, std::vector<SeamCarvingEdit> *energyModifiers = NULL);

			Image* SeamCarvingUpsize(int horizontalUpsize, int verticalUpsize, SeamCarvingType type = BEST_PATH, std::vector<SeamCarvingEdit> *energyModifiers = NULL);

			GLushort GetWidth() const;
			GLushort GetHeight() const;
			GLushort GetBytesPerPixel() const;

			GLint GetGLFormat() const;
			InternalFormatType GetFormat() const;

			bool HaveAlphaChannel() const;

			const BYTE* GetImageData() const;
			const BYTE* GetPixelPointer(const GLushort &x, const GLushort &y) const;
			Color GetPixel(GLushort x, GLushort y) const;
			void SetPixel(const GLushort &x, const GLushort &y, const Color &c);

			static void SeamCarvingAddRectangleEnergyModifier(std::vector<SeamCarvingEdit> *energyModifiers, int x, int y, int xSize, int ySize, double add, double multiply = 1.0);

		protected:
			static void SeamCarvingVerticalExtendSeam(int *dest, int *src, int height);
			static Image* SeamCarvingAddVertical(int *seam, Image *img);
			static void ApplyVerticalSeamOnEnergyModifiers(std::vector<SeamCarvingEdit> *energyModifiers, int *seam, int height);
			static void SeamCarvingApplyEnergyModifiers(double *energyMap, int width, int height, std::vector<SeamCarvingEdit> *energyModifiers);
			static void RotateEnergyModifiersClockwise(std::vector<SeamCarvingEdit> *energyModifiers, int width, int height);
			static void RotateEnergyModifiersCounterClockwise(std::vector<SeamCarvingEdit> *energyModifiers, int width, int height);
			static int* GetSeam(Image *img, SeamCarvingType type = BEST_PATH, std::vector<SeamCarvingEdit> *energyModifiers = NULL);

			void BlitSafe(Image *image, Point point, Rect rect);

			GLushort m_width;
			GLushort m_height;
			GLushort m_GLFormatType;
			GLushort m_bytesPerPixel;

			InternalFormatType m_internalFormatType;

			BYTE *m_imageBuffer;

			friend Core::ReturnValue LoadTGA(Image *image, const std::string &path, bool flipForOpenGL);
			friend Core::ReturnValue SaveTGA(Image *image, const std::string &path);

			friend Core::ReturnValue LoadPNG(Image *image, const std::string &path, bool flipForOpenGL);
			friend Core::ReturnValue SavePNG(Image *image, const std::string &path);

			friend Core::ReturnValue LoadPPM(Image *image, const std::string &path, bool flipForOpenGL);
			friend Core::ReturnValue SavePPM(Image *image, const std::string &path);
		};

		GLushort GetBPP(GLint format);
	}
}

#endif

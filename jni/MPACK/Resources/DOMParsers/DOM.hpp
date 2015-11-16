#ifndef MPACK_DOM_HPP
#define MPACK_DOM_HPP

#include "Types.hpp"
#include "SearchList.hpp"

namespace MPACK
{
	namespace Core
	{
		class JSONParser;
	}
}

namespace MPACK
{
	namespace Core
	{
		class DOM : public Uncopyable
		{
		public:
			DOM();
			DOM(std::string value, bool isTerminal);
			~DOM();

			void Clear();
			void DeleteChilds();
			void DeleteProperties();
			void DeleteArray();

			Algorithm::SearchList<std::string,DOM*>& Childs();
			Algorithm::SearchList<std::string,DOM*>& Properties();

			void AddString(std::string value, std::string key = "");

			DOM* At(int index) const;
			DOM* Child(std::string child);
			DOM* Property(std::string property);

			bool IsArray() const;
			bool IsTerminal() const;
			bool IsValid() const;

			std::string GetValue() const;
			void SetValue(std::string value);

			static DOM* GetSentinel();

		private:
			Algorithm::SearchList<std::string,DOM*> m_childs;
			Algorithm::SearchList<std::string,DOM*> m_properties;
			std::vector<DOM*> m_array;

			bool m_isTerminal;
			bool m_isArray;
			std::string m_value;

			static DOM s_sentinel;

			friend class JSONParser;
		};
	}
}

#endif

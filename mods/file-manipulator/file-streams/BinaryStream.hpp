#pragma once

#include "FileStream.hpp"

namespace wrd
{
	namespace fm
	{
		class File;
		
		class BinaryStream : public FileStream
		{	WRD_INHERIT(BinaryStream, FileStream)
		public:
			BinaryStream();
			BinaryStream(const std::string& new_path);
			BinaryStream(const File& file);
			virtual ~BinaryStream();

		public:
			using FileStream::operator=;
			
			virtual wbool init();

			using FileStream::write;
			template <typename T>
			wcnt write(const T& datum) { return write(&datum, sizeof(T)); }

			wcnt write(const char* str);
			wcnt write(const std::string& str);
			virtual wcnt write(const void* chunks, wcnt bytes);
			virtual wcnt read(void* target, wcnt bytes);

			using FileStream::read;
			template <typename T>
			T read()
			{
				T to_return;
				read(&to_return, sizeof(T));
				return to_return;
			}

			std::string read(wcnt bytes);

		private:
			BinaryStream(const PathedObject& object);

		};
	}
}
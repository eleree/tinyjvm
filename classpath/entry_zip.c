#include "entry.h"
#include "../strings/strings.h"
#include "../miniz/miniz.c"

int64_t readZipEntryClass(const char * zippath, const char * className, char ** classContent)
{	
	if (stringHasSuffix(zippath, ".jar") == 0 || stringHasSuffix(zippath, ".JAR") == 0 ||
		stringHasSuffix(zippath, ".zip") == 0 || stringHasSuffix(zippath, ".ZIP") == 0)
	{
		int file_index = 0;
		mz_zip_archive zipArchive = { 0 };
		mz_zip_archive_file_stat file_stat = { 0 };

		if (mz_zip_reader_init_file(&zipArchive, zippath, 0) == MZ_FALSE)
		{
			printf("Failed to open zip file\n");
			exit(1);
		}
		printf("Open zip file success\n");

		printf("Total Files:%d\n", mz_zip_reader_get_num_files(&zipArchive));

		file_index = mz_zip_reader_locate_file(&zipArchive, className, NULL, 0);

		if (!mz_zip_reader_file_stat(&zipArchive, file_index, &file_stat))
		{
			printf("Failed to get zip file info,fileIndex:%d\n", file_index);
			exit(1);
		}

		size_t uncompressed_size = (size_t)file_stat.m_uncomp_size;
		void* p = mz_zip_reader_extract_file_to_heap(&zipArchive, file_stat.m_filename, &uncompressed_size, 0);
		if (!p)
		{
			printf("Failed to unzip file data\n");
			exit(1);
		}

		//printf("Poem %s:", file_stat.m_filename);
		//for (int i = 0; i < (int)uncompressed_size; i++)
		//{
		//	printf("%c", *((char *)p + i));
		//}
		//printf("\n");
		//mz_free(p);
		*classContent = p;
		mz_zip_reader_end(&zipArchive);
		return file_stat.m_uncomp_size;
	}

	return -1;
}
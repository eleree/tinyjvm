#include "miniz.c"
#include <stdio.h>
#include <stdlib.h>

void testMinizWrapper(void)
{
	mz_zip_archive zipArchive = { 0 };
	mz_zip_archive_file_stat file_stat = { 0 };

	if (mz_zip_reader_init_file(&zipArchive, "E:/2016/tinyjvm/Debug/test.zip",0) == MZ_FALSE)
	{
		printf("Failed to open zip file\n");
		exit(1);
	}
	printf("Open zip file success\n");

	printf("Total Files:%d\n",mz_zip_reader_get_num_files(&zipArchive));
	
	if (!mz_zip_reader_file_stat(&zipArchive, 0, &file_stat))
	{
		printf("Failed to get zip file info\n");
		exit(1);
	}
	
	size_t uncompressed_size = file_stat.m_uncomp_size;
	void* p = mz_zip_reader_extract_file_to_heap(&zipArchive, file_stat.m_filename, &uncompressed_size, 0);
	if (!p)
	{
		printf("Failed to unzip file data\n");
		exit(1);
	}

	printf("Poem:");
	for (int i = 0; i < (int) uncompressed_size; i++)
	{
		printf("%c", *((char *)p + i));
	}
	printf("\n");
	mz_free(p);
	mz_zip_reader_end(&zipArchive);
}
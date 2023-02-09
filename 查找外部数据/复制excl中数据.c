
#include"main.h"

int main(void)
{
	//打开文件
	FILE* pfile = fopen("C:\\Users\\15032\\Desktop\\附件1 弱覆盖栅格数据(筛选).csv", "rb");//‘*’间接寻址运算符，‘&’取地址运算符
	if (pfile == NULL) {
		printf("open file failed!\n");
		exit(0);
	}

	//读取文件长度,读完后把文件指针复位到开头
	fseek(pfile, 0, SEEK_END);//将指针位置放到文本末尾(文件，偏移量，偏移起始位置）
	int file_length = ftell(pfile);//读取指针所在的位置的字节数
	rewind(pfile);//返回指针到开头位置

	//申请一段内存空间用来放文件中的文本内容，并置零
	int text_length = file_length * sizeof(char) + 1;
	char* text_buffer = (char*)malloc(text_length);//malloc动态分配内存长度,返回内存地址
	memset(text_buffer, 0, text_length);//复制0到text_buffer的前text_length个字符

	//把文件文本内容读到申请的内存空间中
	int read_length = fread(text_buffer, 1, file_length, pfile);
	if (read_length != file_length) {
		printf("read file failed!\n");
		exit(0);
	}

	//打印文件文本内容，释放申请的内存空间，关闭文件流
	printf(text_buffer);
	free(text_buffer);//释放空间
	fclose(pfile);//关闭流
}

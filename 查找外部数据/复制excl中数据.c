
#include"main.h"

int main(void)
{
	//���ļ�
	FILE* pfile = fopen("C:\\Users\\15032\\Desktop\\����1 ������դ������(ɸѡ).csv", "rb");//��*�����Ѱַ���������&��ȡ��ַ�����
	if (pfile == NULL) {
		printf("open file failed!\n");
		exit(0);
	}

	//��ȡ�ļ�����,�������ļ�ָ�븴λ����ͷ
	fseek(pfile, 0, SEEK_END);//��ָ��λ�÷ŵ��ı�ĩβ(�ļ���ƫ������ƫ����ʼλ�ã�
	int file_length = ftell(pfile);//��ȡָ�����ڵ�λ�õ��ֽ���
	rewind(pfile);//����ָ�뵽��ͷλ��

	//����һ���ڴ�ռ��������ļ��е��ı����ݣ�������
	int text_length = file_length * sizeof(char) + 1;
	char* text_buffer = (char*)malloc(text_length);//malloc��̬�����ڴ泤��,�����ڴ��ַ
	memset(text_buffer, 0, text_length);//����0��text_buffer��ǰtext_length���ַ�

	//���ļ��ı����ݶ���������ڴ�ռ���
	int read_length = fread(text_buffer, 1, file_length, pfile);
	if (read_length != file_length) {
		printf("read file failed!\n");
		exit(0);
	}

	//��ӡ�ļ��ı����ݣ��ͷ�������ڴ�ռ䣬�ر��ļ���
	printf(text_buffer);
	free(text_buffer);//�ͷſռ�
	fclose(pfile);//�ر���
}

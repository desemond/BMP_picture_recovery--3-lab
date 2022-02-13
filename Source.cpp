#include "Bmp.h"


using namespace std;
void bmp_read_pixels(int size, int* bleu, int* green, int* red, int* alfa) {//������ ���� bmp � ����� � ������� �������� ������ ��� ������� �������
    BMP pict("C:\\Users\\namel\\source\\repos\\������ ����\\������ ����\\17e.bmp");//��������� bmp ����
    int channels = pict.bmp_info_header.bit_count / 8;
    for (int i = 0; i < size; i++) {//���������� �������� ������ � �������������� �������
        bleu[i] = pict.data[channels * i + 0];
        green[i] = pict.data[channels * i + 1];
        red[i] = pict.data[channels * i + 2];
        if (channels == 4) {
            alfa[i] = pict.data[channels * i + 3];
        }
    }
}
void readtxt(int size,int map[]) {//������ txt ����
    string line;
    ifstream f;
    f.open("17.txt");//��������� ����
    if (f.is_open())
    {
        for (int i = 0; i < size; i++)
        {
                f >> map[i];//���������� � ������
        }
        f.close();
    }
    else {
        cout << "eror" << endl;
    }   
}

void heapify(int mas_to_sort[], int n, int i, int* bleu, int* green, int* red, int* alfa)
{
    int largest = i;
    // �������������� ���������� ������� ��� ������
    int l = 2 * i + 1; // �����
    int r = 2 * i + 2; // ������

 // ���� ����� ��� ������ �������� ������� ������, ��� ����� ������� ������� �� ������ ������
    if (l < n && mas_to_sort[l] > mas_to_sort[largest])
        largest = l;
    if (r < n && mas_to_sort[r] > mas_to_sort[largest])
        largest = r;
    // ���� ����� ������� ������� �� ������
    if (largest != i)
    {
        swap(mas_to_sort[i], mas_to_sort[largest]);
        swap(bleu[i], bleu[largest]);
        swap(green[i], green[largest]);
        swap(red[i], red[largest]);
        swap(alfa[i], alfa[largest]);

        // ���������� ����������� � �������� ���� ���������� ���������
        heapify(mas_to_sort, n, largest,bleu,green,red,alfa);
    }
}
//������� ����������� ������������� ����������
void heapSort(int* input, int n, int* bleu, int* green, int* red, int* alfa)
{
    // ���������� ���� (�������������� ������)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(input, n, i, bleu, green, red, alfa);

    // ���� �� ������ ��������� �������� �� ����
    for (int i = n - 1; i >= 0; i--)
    {
        // ���������� ������� ������ � �����
        swap(input[0], input[i]);
        swap(bleu[0], bleu[i]);
        swap(green[0], green[i]);
        swap(red[0], red[i]);
        swap(alfa[0], alfa[i]);
        // �������� ��������� heapify �� ����������� ����
        heapify(input, i, 0, bleu, green, red, alfa);
    }
}
void write_bmp(int x, int y, int* bleu, int* green, int* red, int* alfa) {
    BMP outpict(x, y);
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            int b = bleu[i * y + j];
            int g = green[i * y + j];
            int r = red[i * y + j];
            //int a = alfa[i * x + j];
            //cout << b << " " << g << " " << r << " " << " " << endl;
            outpict.set_pixel(i,j, b, g, r, 255);
        }
    }
    outpict.write("result picture2.bmp");
}

int main() {
    int x, y, size;
    BMP pict("17e.bmp");//��������� ���� bmp
    x = pict.bmp_info_header.width;//�������� ������ ����� bmp
    y = pict.bmp_info_header.height;//�������� ������ �����bmp
    size = x * y;

    //������ ������� ������ ��� ������� bmp ��� �� ������ ������ ���������� ��� �������� � ������ ������
    int* bleu = new int[size];
    int* green = new int[size];
    int* red = new int[size];
    int* alfa = new int[size];
    //������� ������ ��� ����
    int* input = new int[size];
    //������ txt ����
	readtxt(size,input);
    //������ bmp ����
    bmp_read_pixels(size, bleu, green, red, alfa);
    //���������
    heapSort(input, size, bleu, green, red, alfa);
    //������� ����� ���� � ����� � ���� ����������� �����
    write_bmp(y,x, bleu, green, red, alfa);
    return 0;
}
//��������� ���� �������� �������� ����� ����� ��������� �� 90 ��������
//bmp.h ��� ���� � ������� ������� �������� https://github.com/sol-prog/cpp-bmp-images/blob/master/BMP.h

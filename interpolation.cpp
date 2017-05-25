#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include <string>
#include <stdio.h>
#include <math.h>

using namespace cv;
using namespace std;

int main()
{

	Mat img, dst;
	float tmp1 = 0, tmp2 = 0, d1, d2;
	int cnt = 0;

	img = imread("D:\\opencv\\sources\\doc\\Lena_color.png");
	dst = Mat::zeros(768, 768, img.type());
	//768

	for (int i = 0; i < img.rows; i++) {
		for (int j = 0; j < img.cols; j++) {
			for (int k = 0; k < 3; k++) {
				dst.at<Vec3b>(i*1.5, j*1.5)[k] = img.at<Vec3b>(i, j)[k];

			}
		}
	}

	for (int i = 1; i < dst.rows - 1; i++) {
		for (int j = 1; j < dst.cols - 1; j++) {
			for (int k = 0; k < 3; k++) {
				if (dst.at<Vec3b>(i, j)[k] == 0) { // (i -- ���η� ������ , j -- ���η� ������)

					for (int s = 1; s < dst.rows - 1; s++) { // �켱 �¿�� �ȼ��� �ִ��� ã��, ������ �� �ΰ��� ���Ѵ�
						if (i - s >= 0 && i + s <= dst.rows - 1) {
							if (dst.at<Vec3b>(i - s, j)[k] != 0) { // ���ʹ��� �ȼ� Ȯ��
								if (tmp1 == 0) {
									tmp1 = dst.at<Vec3b>(i - s, j)[k];
									d1 = s;
								}
							}
							if (dst.at<Vec3b>(i + s, j)[k] != 0) { // �����ʹ��� �ȼ� Ȯ��
								if (tmp2 == 0) {
									tmp2 = dst.at<Vec3b>(i + s, j)[k];
									d2 = s;
								}
							}
						}
						if (tmp1 != 0 && tmp2 != 0) { // �¿� ���� �ȼ��� �� ã������ ������ �Ÿ� ������ŭ ����ġ ����
							dst.at<Vec3b>(i, j)[k] = tmp1*(d2 / (d1 + d2)) + tmp2*(d1 / (d1 + d2));
							tmp1 = 0;
							tmp2 = 0;
							printf("%d / 976904 ������...\n", cnt++);
							break; // ���̻� ã�� �ʿ� ������ �����ٷ� �̵�
						}
					}
				}

			}
		}
	}

	tmp1 = 0;
	tmp2 = 0;

	for (int i = 1; i < dst.rows - 1; i++) { // �¿쿡 �ȼ����� ���� �ٿ��� ������ ã�� ���� �̿��� �̹��� 
											 // ���Ʒ� �������� �̿� �ȼ� ã�Ƽ� �� �ȼ����� ���� ���� ä���
		for (int j = 1; j < dst.cols - 1; j++) {
			for (int k = 0; k < 3; k++) {
				if (dst.at<Vec3b>(i, j)[k] == 0) {

					for (int s = 1; s < dst.rows - 1; s++) {
						if (j - s >= 0 && j + s <= dst.rows - 1) {
							if (dst.at<Vec3b>(i, j - s)[k] != 0) { // ���� ���� ����
								if (tmp1 == 0) {
									tmp1 = dst.at<Vec3b>(i, j - s)[k];
									d1 = s;
								}
							}
							if (dst.at<Vec3b>(i, j + s)[k] != 0) { // �Ʒ����� ����
								if (tmp2 == 0) {
									tmp2 = dst.at<Vec3b>(i, j + s)[k];
									d2 = s;
								}
							}
						}
						if (tmp1 != 0 && tmp2 != 0) { // ���� �̿� �ȼ� ã������ ����ġ ���� �� ���ȼ������� ä��
							printf("%d / 976904 ������...\n", cnt++);
							dst.at<Vec3b>(i, j)[k] = tmp1*(d2 / (d1 + d2)) + tmp2*(d1 / (d1 + d2));
							tmp1 = 0;
							tmp2 = 0;
							break;
						}
					}
				}

			}
		}
	}

	imshow("Original", img);
	imshow("Result", dst);

	waitKey(0);
	return 0;

}
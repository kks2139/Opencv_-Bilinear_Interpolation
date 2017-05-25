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
				if (dst.at<Vec3b>(i, j)[k] == 0) { // (i -- 세로로 움직임 , j -- 가로로 움직임)

					for (int s = 1; s < dst.rows - 1; s++) { // 우선 좌우로 픽셀이 있는지 찾고, 있으면 그 두값을 취한다
						if (i - s >= 0 && i + s <= dst.rows - 1) {
							if (dst.at<Vec3b>(i - s, j)[k] != 0) { // 왼쪽방향 픽셀 확인
								if (tmp1 == 0) {
									tmp1 = dst.at<Vec3b>(i - s, j)[k];
									d1 = s;
								}
							}
							if (dst.at<Vec3b>(i + s, j)[k] != 0) { // 오른쪽방향 픽셀 확인
								if (tmp2 == 0) {
									tmp2 = dst.at<Vec3b>(i + s, j)[k];
									d2 = s;
								}
							}
						}
						if (tmp1 != 0 && tmp2 != 0) { // 좌우 방향 픽셀값 다 찾았을때 떨어진 거리 비율만큼 가중치 적용
							dst.at<Vec3b>(i, j)[k] = tmp1*(d2 / (d1 + d2)) + tmp2*(d1 / (d1 + d2));
							tmp1 = 0;
							tmp2 = 0;
							printf("%d / 976904 수행중...\n", cnt++);
							break; // 더이상 찾을 필요 없으니 다음줄로 이동
						}
					}
				}

			}
		}
	}

	tmp1 = 0;
	tmp2 = 0;

	for (int i = 1; i < dst.rows - 1; i++) { // 좌우에 픽셀들이 없는 줄에서 위에서 찾은 값을 이용해 이번엔 
											 // 위아래 방향으로 이웃 픽셀 찾아서 빈 픽셀들을 위와 같이 채운다
		for (int j = 1; j < dst.cols - 1; j++) {
			for (int k = 0; k < 3; k++) {
				if (dst.at<Vec3b>(i, j)[k] == 0) {

					for (int s = 1; s < dst.rows - 1; s++) {
						if (j - s >= 0 && j + s <= dst.rows - 1) {
							if (dst.at<Vec3b>(i, j - s)[k] != 0) { // 위쪽 방향 수색
								if (tmp1 == 0) {
									tmp1 = dst.at<Vec3b>(i, j - s)[k];
									d1 = s;
								}
							}
							if (dst.at<Vec3b>(i, j + s)[k] != 0) { // 아래방행 수색
								if (tmp2 == 0) {
									tmp2 = dst.at<Vec3b>(i, j + s)[k];
									d2 = s;
								}
							}
						}
						if (tmp1 != 0 && tmp2 != 0) { // 양쪽 이웃 픽셀 찾았으면 가중치 적용 후 빈픽셀값으로 채움
							printf("%d / 976904 수행중...\n", cnt++);
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
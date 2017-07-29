/*
 *
 * This file is part of the open-source SeetaFace engine, which includes three modules:
 * SeetaFace Detection, SeetaFace Alignment, and SeetaFace Identification.
 *
 * This file is part of the SeetaFace Identification module, containing codes implementing the
 * face identification method described in the following paper:
 *
 *   
 *   VIPLFaceNet: An Open Source Deep Face Recognition SDK,
 *   Xin Liu, Meina Kan, Wanglong Wu, Shiguang Shan, Xilin Chen.
 *   In Frontiers of Computer Science.
 *
 *
 * Copyright (C) 2016, Visual Information Processing and Learning (VIPL) group,
 * Institute of Computing Technology, Chinese Academy of Sciences, Beijing, China.
 *
 * The codes are mainly developped by Wanglong Wu(a Ph.D supervised by Prof. Shiguang Shan)
 *
 * As an open-source face recognition engine: you can redistribute SeetaFace source codes
 * and/or modify it under the terms of the BSD 2-Clause License.
 *
 * You should have received a copy of the BSD 2-Clause License along with the software.
 * If not, see < https://opensource.org/licenses/BSD-2-Clause>.
 *
 * Contact Info: you can send an email to SeetaFace@vipl.ict.ac.cn for any problems. 
 *
 * Note: the above information must be kept whenever or wherever the codes are used.
 *
 */

#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include "face_detection.h"
#include "face_alignment.h"
#include "face_identification.h"

void face_recognizer_test(int argc, char* argv[])
{
	const char* img_path = "mmexport1499927478151.jpg";
	// Initialize face detection model
	seeta::FaceDetection detector("../../../FaceDetection/model/seeta_fd_frontal_v1.0.bin");
	detector.SetMinFaceSize(40);
	detector.SetScoreThresh(2.f);
	detector.SetImagePyramidScaleFactor(0.8f);
	detector.SetWindowStep(4, 4);

	// Initialize face alignment model 
	seeta::FaceAlignment point_detector("../../../FaceAlignment/model/seeta_fa_v1.1.bin");

	// 初始化人脸识别
	seeta::FaceIdentification identification("../../../FaceIdentification/model/seeta_fr_v1.0.bin");

	cv::Mat img = cv::imread(img_path, cv::IMREAD_UNCHANGED);
	cv::Mat img_gray;

	if (img.channels() != 1)
		cv::cvtColor(img, img_gray, cv::COLOR_BGR2GRAY);
	else
		img_gray = img;

	seeta::ImageData img_data;
	img_data.data = img_gray.data;
	img_data.width = img_gray.cols; 
	img_data.height = img_gray.rows;
	img_data.num_channels = 1;

	std::vector<seeta::FaceInfo> faces = detector.Detect(img_data);

	int32_t face_num = static_cast<int32_t>(faces.size());

	if (face_num == 0)
	{
		return;
	}

	//特征提取
	FaceFeatures* features = new FaceFeatures[face_num];
	for (int j = 0;j < face_num;j++)
	{
		seeta::FacialLandmark points[5];
		point_detector.PointDetectLandmarks(img_data, faces[j], points);

		seeta::ImageData img_data_3c;
		img_data_3c.data = img.data;
		img_data_3c.width = img.cols; 
		img_data_3c.height = img.rows;
		img_data_3c.num_channels = 3;

		int size = identification.feature_size();
		features[j] = new float[identification.feature_size()];
		memset(features[j], 0, identification.feature_size() * sizeof(float));
		identification.ExtractFeatureWithCrop(img_data_3c, points, features[j]);
	}

	//
	for (int j = 0;j < face_num;j++)
	{
		for (int i = 0;i < face_num;i++)
		{
			float sim = identification.CalcSimilarity(features[j], features[i]);

			printf("CalcSimilarity(%d, %d) = %f\n", j, i, sim);
		}
	}

	for (int j = 0;j < face_num;j++)
	{
		// Detect 5 facial landmarks
		seeta::FacialLandmark points[5];
		point_detector.PointDetectLandmarks(img_data, faces[j], points);

		// Visualize the results
		cv::rectangle(img, cvPoint(faces[j].bbox.x, faces[j].bbox.y), cvPoint(faces[j].bbox.x + faces[j].bbox.width - 1, faces[j].bbox.y + faces[j].bbox.height - 1), CV_RGB((j == 0) ? 255 : 0, (j == 1) ? 255 : 0, (j == 2) ? 255 : 0));
		for (int i = 0; i<5; i++)
		{
			cv::circle(img, cv::Point(points[i].x, points[i].y), 2, CV_RGB(0, 255, 0), CV_FILLED);
		}
	}

	cv::namedWindow("Test", cv::WINDOW_NORMAL);
	cv::imshow("Test", img);
	cv::waitKey(0);
	cv::destroyAllWindows();

	return;
}
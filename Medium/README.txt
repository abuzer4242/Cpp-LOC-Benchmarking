This C++ program utilizes OpenCV with CUDA support to perform real-time face detection using Haar cascades. It supports both CPU and GPU processing, allowing users to toggle between them dynamically. The program accepts image, video, or camera input and applies face detection using either OpenCV’s standard CascadeClassifier (CPU) or cuda::CascadeClassifier (GPU).

Features:
- Supports real-time face detection with OpenCV.
- Uses CUDA acceleration for faster processing on compatible GPUs.
- Allows dynamic switching between CPU and GPU modes.
- Provides various configuration options, including face filtering and multi-face detection.
- Displays detected faces and FPS performance in a GUI window.

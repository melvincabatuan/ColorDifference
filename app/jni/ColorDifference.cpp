#include "ColorDifference.h"


 	// Default Constructor
    ColorDifference::ColorDifference() : minDist(100){
		target[0] = target[1] = target[2] = 0;
	}
    
    
    // Sets the color distance threshold.
	// Threshold must be positive, otherwise distance threshold is set to 0.
	void ColorDifference::setColorDistanceThreshold(int distance){
	
		if (distance < 0)
			distance = 0;
			
		minDist= distance;
	}
	
	// 15 fps average in 500 frames 
	// Gets the City block color distance (Manhattan distance)  
	int ColorDifference::computeDistance(const cv::Vec3b& color) const {
	
		return abs(color[0]-target[0]) + abs(color[1]-target[1]) + abs(color[2]-target[2]);
	}
	
	
	    // Huge impact on performance: down to 6 fps average after 500 frames
		// Gets the Euclidean Distance (EuclideanDistance)  
	int ColorDifference::computeEuclideanDistance(const cv::Vec3b& color) const {
	
		return static_cast<int>(cv::norm<int,3>(cv::Vec3i(color[0]-target[0], color[1]-target[1], color[2]-target[2])));
	}
	
	
	// Gets the color distance threshold
	int ColorDifference::getColorDistanceThreshold() const {
	
		return minDist;
	}
	
	
	// Sets the color to be detected
	void ColorDifference::setTargetColor(unsigned char red, unsigned char green, unsigned char blue){
	
		// BGR order
		target[2]= red;
		target[1]= green;
		target[0]= blue;
	}
 
	
	// Sets the color to be detected
	void ColorDifference::setTargetColor(cv::Vec3b color){
	
		target= color;
	}
	
	// Gets the color to be detected
	cv::Vec3b ColorDifference::getTargetColor() const {
	
		return target;
	}
	

	// Re-allocate binary map if necessary same size as input image, but 1-channel	
	cv::Mat ColorDifference::process(const cv::Mat &image) {

 	if (result.empty()){
		//result.create(image.rows,image.cols,CV_8U); // for Gray input
		result.create(image.rows,image.cols,CV_8UC3);
	}
	
	// get the iterators
	cv::Mat_<cv::Vec3b>::const_iterator it = image.begin<cv::Vec3b>();
	cv::Mat_<cv::Vec3b>::const_iterator itend = image.end<cv::Vec3b>();
	cv::Mat_<uchar>::iterator itout = result.begin<uchar>();
	
	// for each pixel
	for ( ; it!= itend; ++it, ++itout) {
		// process each pixel ---------------------
		// compute distance from target color
		//if (computeDistance(*it) < minDist) {
		if (computeEuclideanDistance(*it) < minDist) {
			*itout = 255;
		} else {
			*itout = 0;
		}
		// end of pixel processing ----------------
	}
 
	return result;
	}

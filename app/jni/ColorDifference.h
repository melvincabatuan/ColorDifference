/* Taken from R. Laganiere, OpenCV 2 Computer Vision Application Programming Cookbook */

#include <opencv2/core/core.hpp>



class ColorDifference {

private:

	int minDist;      // minimum acceptable color distance
	cv::Vec3b target; // target color
	cv::Mat result;   // image containing resulting binary map

public:

 	// Default Constructor
    ColorDifference();
    
    // Sets the color distance threshold.
	// Threshold must be positive, otherwise distance threshold is set to 0.
	void setColorDistanceThreshold(int distance);
	
	// Computes the City block color distance (Manhattan distance)  
	int computeDistance(const cv::Vec3b& color) const;
	
	// Computes the Euclidean Color Distance
	int computeEuclideanDistance(const cv::Vec3b& color) const;
	
	// Gets the color distance threshold
	int getColorDistanceThreshold() const;
	
	// Sets the color to be detected
	void setTargetColor(unsigned char red, unsigned char green, unsigned char blue);
	
	// Sets the color to be detected
	void setTargetColor(cv::Vec3b color);
	
	// Gets the color to be detected
	cv::Vec3b getTargetColor() const;
	
	// Process the input frames
	cv::Mat process(const cv::Mat &image);  // this will give the result

};

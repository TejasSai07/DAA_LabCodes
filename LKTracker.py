import cv2
import numpy as np

# Parameters for Lucas-Kanade optical flow
lk_params = dict(winSize=(15, 15),
                 maxLevel=2,
                 criteria=(cv2.TERM_CRITERIA_EPS | cv2.TERM_CRITERIA_COUNT, 10, 0.03))

# Load two consecutive frames (for example purposes)
frame1 = cv2.imread('frame1.jpg')
frame2 = cv2.imread('frame2.jpg')

# Convert images to grayscale
gray1 = cv2.cvtColor(frame1, cv2.COLOR_BGR2GRAY)
gray2 = cv2.cvtColor(frame2, cv2.COLOR_BGR2GRAY)

# Detect features in the first frame using SIFT
sift = cv2.SIFT_create()
keypoints1, descriptors1 = sift.detectAndCompute(gray1, None)
keypoints2, descriptors2 = sift.detectAndCompute(gray2, None)

# Match descriptors between frames using BFMatcher
bf = cv2.BFMatcher()
matches = bf.knnMatch(descriptors1, descriptors2, k=2)

# Apply ratio test to filter good matches
good_matches = []
for m, n in matches:
    if m.distance < 0.75 * n.distance:
        good_matches.append(m)

# Extract the matched keypoints
pts1 = np.float32([keypoints1[m.queryIdx].pt for m in good_matches])
pts2 = np.float32([keypoints2[m.trainIdx].pt for m in good_matches])

# Calculate optical flow using the Lucas-Kanade method
p1, st, err = cv2.calcOpticalFlowPyrLK(gray1, gray2, pts1, None, **lk_params)
p1 = p1[st == 1]
pts2 = pts2[st == 1]

# Estimate motion model (Affine or Homography) based on the matched points
motion_model = 'affine'  # Set this to either 'affine' or 'homography'
if motion_model == 'affine':
    M, _ = cv2.estimateAffine2D(pts1, pts2)
elif motion_model == 'homography':
    M, _ = cv2.findHomography(pts1, pts2, cv2.RANSAC)

# Warp the first frame to the second frame using the estimated motion model
if motion_model == 'affine':
    warped_frame1 = cv2.warpAffine(frame1, M, (frame2.shape[1], frame2.shape[0]))
elif motion_model == 'homography':
    warped_frame1 = cv2.warpPerspective(frame1, M, (frame2.shape[1], frame2.shape[0]))

# Display the matched points and the warped frame
matches_img = cv2.drawMatches(frame1, keypoints1, frame2, keypoints2, good_matches, None, flags=2)
cv2.imshow("Matched Features", matches_img)
cv2.imshow("Warped Frame 1 to Frame 2", warped_frame1)
cv2.waitKey(0)
cv2.destroyAllWindows()

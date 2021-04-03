Guidline to run the executable file:

$make
$./a.out <Video_name>		(*<Image_name> to be substituted by the image name
				that is to be processed. Eg: if we want to process
				the empty.jpg image then write
				$./a.out empty	*)

After running the above commands, we have to choose 4 POINTS on the image opened on
the window in ANTI-CLOCKWISE order)
then we will get to see the corrected camera angle and cropped video.
Also the time(in secs),queue density,dynamic density is printed on the
console so that it can be used to plot the graph. 

The data gets saved on the current directory.

We can run the following command on the terminal to delete the out.txt and a.out
that have been saved:

$make clean


def readfile(file_path):
	with open(file_path, 'r') as f:
		frames = f.readlines()
	
	subfolders = [x.split(' ')[0] for x in frames]
	for subfolder in subfolders:
		print(subfolder)

	frame_ids = [x.split(' ')[1][:-1] for x in frames]
	for frame_id in frame_ids:
		print(frame_id)


readfile("/media/mr/file/KITTI_dump/train.txt")

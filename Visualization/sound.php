<?php
	//Take data from the latest updated line in sound_log.txt.
	$data = file("sound_log.txt");
	$line = $data[count($data)-1];
	echo $line;
?>
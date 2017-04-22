<?php	
	$log_file = "sound_log.txt";
	$hds = $_POST["data"];	//Take the data posted from comm.c into the URL.
	date_default_timezone_set["UTC"];
	$str = gmdate("M d Y H:i:s",time()).", ".$hds."\r\n";
	$fp = fopen($log_file,"a");			
	fwrite($fp,$str);
	fclose($f);
	

?>
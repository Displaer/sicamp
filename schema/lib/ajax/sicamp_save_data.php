<?php
session_start();
include("../config.php");
include("../lib.php");
DB_CONNECT();
header("Content-type: text/html; charset=utf-8");
if(isset($_SESSION['fuser']) and isset($_POST['data'])){
	
	$catigory=$_POST['data']['catigory'];
	$group=$_POST['data']['group'];
	$timeline=$_POST['data']['timeline'];
	$donejob=$_POST['data']['donejob'];
	
	$q1 = "SELECT `id` FROM `tbl_donejob` WHERE `criteria_id` = $catigory and `group_id` = $group and `timeline_num` = $timeline;";
	$r1 = mysql_query($q1);
	if($r1){
		if(mysql_num_rows($r1)>0){
			$wr = mysql_fetch_assoc($r1);
			$q="UPDATE `tbl_donejob` SET `done` = '$donejob' WHERE `id` = ".$wr['id']." Limit 1;";
		}else{
			//(`id`, `criteria_id`, `group_id`, `timeline_num`, `done`)
			$q="INSERT INTO `tbl_donejob`  VALUES (NULL, '$catigory', '$group', '$timeline', '$donejob');";
		}
		if(mysql_query($q)){
			$RES = "success";
		}else{
			$RES = "error:".mysql_error();
		}
	}else{
		$RES = "error:".mysql_error();
	}
	echo $RES;
}else{
	header("HTTP/1.0 404 Not Found");
}
?>
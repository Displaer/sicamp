<?php
if(isset($_POST['go']) and isset($_POST['sLogin']) and isset($_POST['sPassword'])){

	$login = mysql_real_escape_string(trim($_POST['sLogin']));
	$paswd = mysql_real_escape_string(trim($_POST['sPassword']));
	$paswd = md5($login.$paswd);
	$q = "SELECT * FROM `tbl_admin` WHERE `login`='".$login."' and `password`='".$paswd."' and `active`=1;";
	$r = mysql_query($q);
	if($r and mysql_num_rows($r)){
		$w = mysql_fetch_assoc($r);
		$_SESSION['fuser'] = $w['id'];
		$_SESSION['fdata'] = $w;
		echo '<p aling="center"><h1>WLCOME ADMINISTRATOR!</h1></p>';
		echo "<meta http-equiv=\"refresh\" content=\"3;url=?control=allgrps\" />";;

	}else{
		login_form();

	}
}else{
	login_form();
}




?>
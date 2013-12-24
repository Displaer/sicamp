<?php
session_start();
header("Content-type: text/html; charset=utf-8");
include("lib/config.php");
include("lib/lib.php");
DB_CONNECT();

/*
$_ip = sd_getip();
if(!($_SERVER['HTTP_USER_AGENT']==' Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.11 (KHTML, like Gecko) Chrome/23.0.1271.97 Safari/537.11')){
echo "HTTP/1.0 status 302: Underconstruction.($_ip)<br > ";
echo $_SERVER['HTTP_USER_AGENT'];
exit;
}
*/


	if(isset($_GET['control']) && $_GET['control']!=''){
		$_SESSION['control']=$_GET['control'];
	} else {
		if(empty($_SESSION['control'])){
			$_SESSION['control']='wellcome';
		} 
	}
	$xcontrol=$_SESSION['control'];

?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title>..:: SICamp 2013 ::..</title>
<script src="res/js/jquery-1.8.2.js" type="text/javascript"></script>
<link href="res/bootstrap/css/bootstrap.min.css" rel="stylesheet" media="screen">
<script src="res/bootstrap/js/bootstrap.min.js"></script>
<script src="res/highcharts/js/modules/exporting.js"></script>
<script src="res/highcharts/js/highcharts.js"></script>
<script src="res/edit.js"></script>
<script type="text/javascript"></script>
<style>
#err_div2 span{
	text-align:center;
	width:90%;
	padding:10px;
}
#banner{
	margin:10px 0 0 50px;
	clear:left;
	white-space:nowrap;
}
#iblock{display:inline-block;}
#menu li{
	list-style:none;
	display:inline-block;
}
#menu a{padding:3px 10px 3px 10px;}
#menu a:hover{border:#666 dotted 1px; background:#CCC;}
#all{padding-top:55px; padding-bottom:55px;}
.logo{
	position:relative;
	margin:10px;
	width:150px;
	}
#footer{
	height:30px;
	background:#666;	
}
.white_foot{
	padding:3px;
	font-family:Verdana, Geneva, sans-serif;
	font-size:12px;
	color:#FFF;
}
</style>
</head>
<body>
	<div class="navbar navbar-inverse navbar-fixed-top">
      <div class="navbar-inner">
        <div class="container">
          <div class="nav-collapse collapse">
            <ul class="nav"><?=get_menu_line($xcontrol)?></ul>
            <ul class="nav pull-right"><?=login_lnk($xcontrol)?></ul>
          </div>
	    </div>
      </div>
    </div>

<!--///////////////////////////////////////////////////////////////-->
<div id="all">
	<div id="banner">
		<div id="iblock">
			<a href="?control=allgrps"><img class="logo" src="assets/images/logo.png" width="150" ></a>
		</div>
		<div id="iblock"><h1>SICamp 2013</h1></div>
	</div>
<table width="100%" border="0" cellspacing="0" cellpadding="0">
  <tr>
    <td>
    
 <div class="navbar">
  <div class="navbar-inner">
    <ul class="nav"><?=get_menu_line($xcontrol)?></ul>
  </div>
</div>
    
    </td>
  </tr>
  <tr>
    <td style="padding:20px;">
    <?
	
		$path_module = "components/".$xcontrol.".inc";
		if(file_exists($path_module)){
			include $path_module;	
		}else{
			echo "<h2>404 - Module not found.</h2>";	
		}
	
	?>
    </td>
  </tr>
</table>
</div>
<!-- //////////////////////////////////////////////////////////////// -->
	<div class="navbar navbar-inverse navbar-fixed-bottom">
			<div id="footer">
			  <div class="container">
					<p align="center" class="white_foot">SICamp &copy; All Right Reserved</p>
			  </div>
			</div>
    </div>

</body>
</html>
<?php

function DB_CONNECT()
{
global $CONN;
$link=mysql_connect($CONN['host'],$CONN['user'], $CONN['password']);
  if(!$link){
  print "Cannaot connect to MySQL DataBase!";
  exit();
  }
   if(!mysql_select_db($CONN['db'],$link)){
	print "Unable to select DataBase!";
	exit();
  }
  
  mysql_query(" SET NAMES utf8;");
 }

 function fetch($q){
	$res=mysql_query($q);
	if($res){
		if ($w=mysql_fetch_array($res)){
			return $w;
		}else{
			return FALSE;
		}
	} else {
		return FALSE;
	}
}


 
function errcap($tx,$w){
$tg=($w=='r')?'label label-important':'label label-success';
echo '<div id="err_div2"><span class="'.$tg.'">'.$tx.'</span></div>';
}

function get_menu_line($action){
	global $_SESSION;
	if(isset($_SESSION['fuser'])){
		$MENU_ACCESS = "";
	}else{
		$MENU_ACCESS = "WHERE `id` <3 ";
	}

	$q="SELECT `key`, `caption` FROM `sys_components` ".$MENU_ACCESS." ORDER BY  `order` ASC;";
	$RES = "";
	$r=mysql_query($q);
	if ($r and mysql_num_rows($r)){
		while ($w=mysql_fetch_array($r)){
			$_class =($w['key']==$action)?'class="active"':'';
			$RES.='<li '.$_class.'><a href="?control='.$w['key'].'">'.$w['caption'].'</a></li>';
		}
	}
	return $RES;
}


function login_lnk($action){
	global $_SESSION;
	if(isset($_SESSION['fuser'])){
		$login = strtoupper($_SESSION['fdata']['login']);
		$_class =($action=='logout')?'class="active"':'';
		$RES.='<li '.$_class.'><a href="?control=logout">Logout '.$login.'</a></li>';
	}else{
		$_class =($action=='login')?'class="active"':'';
		$RES.='<li '.$_class.'><a href="?control=login">Login</a></li>';
	}
	return $RES;
}

function login_form(){
$time = time();
echo '<table align="center" >
<form action="index.php" method="post" name="login">
<tr><td rowspan="3" align="center" valign="middle"><img src="assets/images/login_icon_smal2.gif" width="80" height="72"></td>
<td align="right"><font color="#666666">Логин:</font></td><td><input type="text" name="sLogin" align="middle" value="Введите логин"  
onFocus="javascript:ss=document.login.sLogin.value; if(ss==\'Введите логин\') document.login.sLogin.value=\'\';" 
onBlur="javascript:ss=document.login.sLogin.value; if(ss==\'\') document.login.sLogin.value=\'Введите логин\';"></td></tr>
<tr><td align="right"><font color="#666666">Парол:</font>
</td><td><input type="password" name="sPassword" align="middle" ></td></tr>
<tr><td  align="center" colspan="2"><input class="btn" name="go" value=" В Х О Д " type="submit" ></td></tr>
<input type="hidden" name="sTime" value="'.$time.'">
</form>
</table>';
}

//BEGIN highcharts//

function get_group_percent($gruop, $catigory, $timenum){
	$q = "SELECT `id`, `done` FROM `tbl_donejob` WHERE `criteria_id`= $catigory and  `group_id`=$gruop and `timeline_num` = $timenum ;";
	//echo $q;
	$r = mysql_query($q);
	if($r and mysql_num_rows($r)){
		$w = mysql_fetch_array($r);
		$pc = round($w['done'],2);
	}else{
		$pc = 0;
	}
	return $pc."%";
}

function get_group_percent_max($gruop, $catigory){
	$q = "SELECT MAX(`done`) FROM `tbl_donejob` WHERE `criteria_id`= $catigory and  `group_id`=$gruop;";
	$WR = fetch($q);
	if($WR!==FALSE){
		$pc = round($WR[0],2);
	}else{
		$pc = -1;
	}
	return $pc."%";
}



function get_group_percent_all($group, $timenum){
	$q = "SELECT SUM(`done`) FROM `tbl_donejob` WHERE `group_id` = $group and `timeline_num` = $timenum ;";
	$r = mysql_query($q);
	if($r and mysql_num_rows($r)){
		$w = mysql_fetch_array($r);
		$pc = round(($w[0]/8),2);
	}else{
		$pc = 0;
	}
	return $pc."%";
}

function get_group_percent_all_max($group){
	$q = "SELECT `timeline_num`, SUM(`done`) FROM `tbl_donejob` WHERE `group_id` = $group group by `timeline_num`;";
	$r = mysql_query($q);
	if($r and mysql_num_rows($r)){
		$MAX = 0;
		while($w = mysql_fetch_array($r)){
			$pc = ($w[1]/8);
			if($pc > $MAX) $MAX = $pc;
		}
		$pc = round($MAX,2);
	}else{
		$pc = 0;
	}
	return $pc."%";
}


function get_categories(){
	$q = "SELECT `num`, `day`, `hour` FROM `tbl_timeline` WHERE `num`!=12 ORDER BY `num` ASC";
	$RES_ARR = array();
	$r=mysql_query($q);
	if($r and mysql_num_rows($r)){
		while ($w=mysql_fetch_array($r)){
			array_push($RES_ARR, "'".$w['hour']."'");
		}
	}
	array_push($RES_ARR, "'19:00'");
	return implode(", ", $RES_ARR);
}


function get_series($group){
		$TIME_ARR = array();
		$q = "SELECT `num` FROM `tbl_timeline`;";
		$r = mysql_query($q);
		if($r and mysql_num_rows($r)){
			while($w=mysql_fetch_array($r)){
				array_push($TIME_ARR, $w['num']);
			}
		}
			
		
		$DATA_ARR = array();
		$q = "SELECT `id`, `name` FROM `tbl_criteria` ORDER BY `order` ASC;";
		$r = mysql_query($q);
		if($r and mysql_num_rows($r)){
			while($w=mysql_fetch_array($r)){
				$X_ARR = array();
				foreach($TIME_ARR as $v){
					$wwr = fetch("SELECT `done` FROM `tbl_donejob` WHERE `criteria_id` = ".$w['id']." and `group_id` = $group and `timeline_num` = $v ");
					if($wwr!==FALSE){
						$x = $wwr[0];
					}else{
						$x = 0;
					}
					array_push($X_ARR, $x);
				}
				$just_data = implode(",", $X_ARR);
				array_push($DATA_ARR, "{name: '".$w['name']."', data:[".$just_data."]}");
			}
		}
		
		
		$_all_data = implode(", ", $DATA_ARR) ;
		$_all_data = "[".$_all_data."]";	
		return $_all_data;
}

function get_series_all(){
		$TIME_ARR = array();
		$q = "SELECT `num` FROM `tbl_timeline`;";
		$r = mysql_query($q);
		if($r and mysql_num_rows($r)){
			while($w=mysql_fetch_array($r)){
				array_push($TIME_ARR, $w['num']);
			}
		}
			
		
		$DATA_ARR = array();
		$q = "SELECT `id`, `name`, `head` FROM `tbl_group` WHERE `deleted`=0 ORDER BY `id` ASC;";
		$r = mysql_query($q);
		if($r and mysql_num_rows($r)){
			while($w=mysql_fetch_array($r)){
				$X_ARR = array();
				foreach($TIME_ARR as $v){
					$x = floatval(get_group_percent_all($w['id'], $v));
					array_push($X_ARR, $x);
				}
				$just_data = implode(",", $X_ARR);
				array_push($DATA_ARR, "{name: '".$w['name']."', data:[".$just_data."]}");
			}
		}
		
		
		$_all_data = implode(", ", $DATA_ARR) ;
		$_all_data = "[".$_all_data."]";	
		return $_all_data;
}


function get_series_all_rectangle(){
		$TIME_ARR = array();
		$q = "SELECT `id` FROM `tbl_group` WHERE `deleted`=0 ORDER BY `id` ASC;";
		$r = mysql_query($q);
		if($r and mysql_num_rows($r)){
			while($w=mysql_fetch_array($r)){
				array_push($TIME_ARR, floatval(get_group_percent_all_max($w['id'])));
			}
		}
		
		$_all_data = implode(", ", $TIME_ARR) ;
		return $_all_data;
}


function get_groups(){
	$DATA_ARR = array();
	$q = "SELECT `id`, `name`, `head` FROM `tbl_group` WHERE `deleted`=0 ORDER BY `id` ASC;";
	$r = mysql_query($q);
	if($r and mysql_num_rows($r)){
		while($w=mysql_fetch_array($r)){
			array_push($DATA_ARR, "'".$w['name']."'");
		}
	}
	$data = implode(",", $DATA_ARR);
	return $data;
}
//END highcharts//



 
?>
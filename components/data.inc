<?
if(isset($_SESSION['fuser'])){

/*
print "<pre>\n POST:";
print_r($_POST);
print "\n  GET:";
print_r($_GET);
print "\n  FILES:";
//print_r($_FILES);
print "</pre>";
*/


/*
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
*/

function show_table($group){
	$q="SELECT `name` FROM `tbl_group` where `id`=$group;";
	$WR = fetch($q);
	$group_name = $WR[0];
	$q="SELECT `id`, `name` FROM `tbl_criteria` order by  `order` ASC;";
	$r=mysql_query($q);
	if ($r and mysql_num_rows($r)){
		//<td>&nbsp;</td>
		echo '<table width="1000" border="1" cellspacing="0" cellpadding="0" class="table table-bordered table-striped">';
		echo '<tr>
			<td colspan=2><h4>'.$group_name.'</h4></td>
			<td colspan="4" align="center"><strong>30 июня</strong></td>
			<td colspan="4" align="center"><strong>1 июля</strong></td>
			<td colspan="4" align="center"><strong>2 июля</strong></td>
		  </tr>
		  <tr>
			<td>&nbsp;</td>
			<td>&nbsp;</td>
			';
			$q_sub="SELECT `num`, `day`, `hour` FROM `tbl_timeline` order by `num` ASC;";
			$r_sub=mysql_query($q_sub);
			$FETCHARR = Array();
			if ($r_sub and mysql_num_rows($r_sub)){
				while ($w_sub=mysql_fetch_array($r_sub)){
					echo '<td align="center"><strong>'.$w_sub['hour'].'</strong></td>';
					array_push($FETCHARR, $w_sub);
				}
				echo '<td align="center"><strong>ИТОГ</strong></td>';
				
			}
			echo '</tr>';
		while ($w=mysql_fetch_array($r)){
			echo '<tr>';
			echo '<td>'.$w['id'].'</td>';
			echo '<td>'.$w['name'].'</td>';
			$criteria_id=$w['id'];
			foreach($FETCHARR as $xw){
				$elm_id = "row_".$group."_".$xw['num']."_".$w['id'];
				$elm_data = "group:".$group.",timeline:".$xw['num'].",catigory:".$w['id'];
				//href="#myModal" data-toggle="modal"
				echo '<td><button class="btn popups" id="'.$elm_id.'" data="'.$elm_data.'">';
				echo get_group_percent($group, $w['id'], $xw['num']);
				echo '</button></td>';
			}
			echo '<td>';
			echo get_group_percent_max($group, $w['id']);
			echo '</td>';
			echo '</tr>';
		}
		
		echo '<td>&nbsp;</td>';
		echo '<td>ИТОГО %</td>';
		foreach($FETCHARR as $xw){
				$elm_id = "sum_".$group."_".$xw['num'];
				echo '<td><span id="" data="'.$elm_id.'">';
				echo get_group_percent_all($group, $xw['num']);
				echo '</span></td>';
		}
		echo '<td>';
		echo '</td>';
		echo '</table>';
		
	}
	echo '<div id="myModal" class="modal hide fade" tabindex="-1" role="dialog" aria-labelledby="myModalLabel" aria-hidden="true">
  <div class="modal-header">
    <button type="button" class="close" data-dismiss="modal" aria-hidden="true">×</button>
    <h3 id="myModalLabel">Введите выполненую работу в %</h3>
  </div>
  <div class="modal-body">
    <p id="modal_content">
		<label for="modal_data" >Выполнено(%):<input type="text" id="modal_data" value=""/></label>
	</p>
  </div>
  <div class="modal-footer">
    <button id="modal_save" class="btn btn-primary">Save</button>
    <button id="modal_close" class="btn" data-dismiss="modal" aria-hidden="true">Close</button>
  </div>
</div>';

}



function show_list(){
$q="SELECT `id`, `name`, `head` FROM `tbl_group` WHERE `deleted`=0 order by  `id` ASC";
$r=mysql_query($q);
if ($r){
	$count = mysql_num_rows($r);
	//width=\"90%\"
	print "<table  align=\"center\" border=\"0\" cellspacing=\"0\" cellpadding=\"0\" class=\"table table-bordered table-striped\">
			<tr>
			    <th>Группа</th>
			    <th>Проект</th>
			    <th>&nbsp;</th>
			</tr>";
	while ($w=mysql_fetch_array($r)){
		$id=$w['id'];
		$name=$w['name'];
		$head=$w['head'];
		$table_link ='index.php?action=table&id='.$id;
		$diagram_link ='index.php?action=diagram&id='.$id;
		$table_link = '<a href="'.$table_link.'">Ввод данных</a>';
		echo  "<tr>";
			echo  '<td>'.$name.'</td>';
			echo  '<td>'.$head.'</td>';
			echo  '<td>'.$table_link.'</td>';
		echo  "</tr>";
	}

	print "</table>";
}
}



if (isset($_POST['action'])){
	$action=$_POST['action'];
} else {
	if (isset($_GET['action'])){
		$action=$_GET['action'];
	} else {
		$action="show";
	}
}

if (isset($action)){
	switch($action){
		case "flist":
		{
			if (isset($_POST['edit'])){
				$id=$_POST['id'];
				$q="SELECT * FROM `file`  where `id`=$id;";
				$r=mysql_query($q);
				if ($r && mysql_num_rows($r)>0){
					$w=mysql_fetch_assoc($r);
					form_adit("edit",$w);
				}
			
			
			} elseif(isset($_POST['delete'])){
				$id=$_POST['id'];
				$d=delete_file($id);
				$q="DELETE From `file` WHERE `id`=$id LIMIT 1 ;";
				$r=mysql_query($q);
				if ($r && $d){
					errcap('Запись удалено успещно', 'g');
				} else {
					errcap('Запись удалить не удалось', 'r');
				}	
				show_list();
			}
		
		}
		break;
		case "table":
		{
			show_table(intval($_GET['id']));
		}
		break;
		case "diagram":
		{
			show_diagram(intval($_GET['id']));
		}
		break;
		case "save":
		{
			////////////////////////////////////////////////////////////
			
		$sact=$_POST['sact'];
		
		$id=$_POST['id'];
		$name=$_POST['name'];
		$comment=$_POST['comment'];
		$ad_date= date("Y-m-d H:i:s");
		$doupload=isset($_POST['doupload']);
		$doreplace=isset($_POST['doreplace']);
		
		if (isset($_POST['button'])){
		
		if ($sact=="add"){

			if (!$doupload){
				errcap('Заполните форму правелно!!!','r');
			} else {
		
		
		
			//file
		if ($doupload && isset($_FILES['upload_file'])){	
				$remote_file=$_FILES['upload_file']['tmp_name'];
				$vname=$_FILES['upload_file']['name'];
				$error=$_FILES['upload_file']['error'];
			if($error > 0){
				errcap('Ошибка загрузки файла !!','r');
			} else {
				
				$name=($name=="")?$vname:$name;
				$vname=get_name($vname);
				$vname_c=$vname;
				$path="userfiles/".$vname;    //path to be reached from the client side
				$fullpath="userfiles/".$vname;
				$ifi=1;
				while(file_exists($path)){
					$vname="cp_".$ifi."_".$vname_c; 
					$path="userfiles/".$vname;    //path to be reached from the client side
					$fullpath="userfiles/".$vname;
					$ifi++;
				}
				
				if (move_uploaded_file($remote_file,$path)){
				
	$q="INSERT INTO `file` ( 
	`id`,
	`name`, 
	`path`, 
	`comment`, 
	`ddate` 
				) VALUES (
    'NULL',
	'$name', 
	'$fullpath', 
	'$comment', 
	'$ad_date' 
	); ";
		
			if (mysql_query($q)){
				errcap('Запись добавлено успещно','g');
			} else {
				errcap('Запись добавить не удалось','r');
			}
		} else {
			errcap('Внутренняя  ошибка сервера!!', 'r');
		} //copy
		}//file error
		}//file
		} // doupload
		
		} elseif($sact=="update"){
		//////////////////////////////////////////
			
		$copy_upload=0;	
		
		if ($doupload && isset($_FILES['upload_file']) && $doreplace){
		
				$remote_file=$_FILES['upload_file']['tmp_name'];
				$vname=$_FILES['upload_file']['name'];
				$error=$_FILES['upload_file']['error'];
			if($error > 0){
				print "<p align=\"center\" class=\"cap\">Ошибка загрузки файла !!</p>";
			} else {
				$copy_upload++;		
				$name=($name=="")?$vname:$name;
				$vname=get_name($vname);
				$vname_c=$vname;
				$path="userfiles/".$vname;    //path to be reached from the client side
				$fullpath="userfiles/".$vname;
				$ifi=1;
				while(file_exists($path)){
					$vname="cp_".$ifi."_".$vname_c; 
					$path="userfiles/".$vname;    //path to be reached from the client side
					$fullpath="userfiles/".$vname;
					$ifi++;
				}
				
				/////////////////////////   DELETE LAST FILE  ///////////////////////////
				if (delete_file($id)) $copy_upload++;	
					
				/////////////////////////   DELETE LAST FILE  ///////////////////////////
				
				
				if (move_uploaded_file($remote_file,$path)){ 
					$copy_upload++;
					errcap("Файл $name был скопирован в сервер!!", 'g');
				} else {
					errcap("Капирования Файла $name завершилась неудачей!!",'r');
				}
				
			} //standart errorsия 
		}// check file data
		
		if ($doupload){
			if ($copy_upload==3){
			
			$q="UPDATE `file` SET 
				 `name` = '$name',
				 `path` = '$fullpath',
				 `comment` = '$comment'
				  WHERE `id` =$id LIMIT 1 ;";
			if (mysql_query($q)){
				errcap('Запись обновлено успещно.','g');
			} else {
				errcap('Запись обновить не удалось','r');
			}
			
			}else{
				errcap('Попытка добавлен файла прервана, попробуйте еще раз!!','r');
			}
		}  else {
		
		
		$q="UPDATE `file` SET 
				 `name` = '$name',
				 `comment` = '$comment'
				  WHERE `id` =$id LIMIT 1 ;";
		   if (mysql_query($q)){
				errcap('Запись обновлено успещно','g');
			} else {
				errcap('Запись обновить не удалось', 'r');
			}
		
		}
		
			
			
		
		
		
		/*
		if (isset($_POST['editpass'])){
			$UP=" `password` = '$password', ";
		} else {
			$UP="";
		}
			
		$id=$_POST['id'];
		$q="UPDATE `file_users` SET `fio` = '$fio',
`login` = '$login', $UP `status` = '$status' WHERE `id` =$id LIMIT 1 ;";
			if (mysql_query($q)){
				print "<p align=\"center\" class=\"cap\">Запись обновлено успещно</p>";
			} else {
				print "<p align=\"center\" class=\"cap\">Запись обновить не удалось</p>";
			}
			*/
				////////////////////////////////////////////////////////////
			}//sact
		}//chack
			show_list();
		}
		break;
		case "show":
		{
			show_list();
		}
		break;
		default:
		{
			show_list();
		}
		break;
	
	}
}


}else{
	echo "<h2>404 - Module not found.</h2>";	
}//fuser
?>
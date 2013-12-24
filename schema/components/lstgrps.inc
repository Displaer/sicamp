<?

/*
print "<pre>\n POST:";
print_r($_POST);
print "\n  GET:";
print_r($_GET);
print "\n  FILES:";
//print_r($_FILES);
print "</pre>";
*/








function show_diagram($group){
	//src="res/chart_1.0.0.js"
	$q="SELECT `name`, `head` FROM `tbl_group` where `id`=$group;";
	$WR = fetch($q);
	$group_name = $WR['name'];
	$group_head = $WR['head'];
	
	
	
	
	$for_js_categories=get_categories();
	$for_js_series=get_series($group);
	
	
	echo '<script>
	$(function () {
        $(\'#container\').highcharts({
            chart: {
                type: \'line\',
                marginRight: 130,
                marginBottom: 25
            },
            title: {
                text: \''.$group_name.'\',
                x: -20 //center
            },
            subtitle: {
                text: \''.$group_head.'\',
                x: -20
            },
            xAxis: {
                categories: ['.$for_js_categories.']
            },
            yAxis: {
                title: {
                    text: \'Выполненно %\'
                },
                plotLines: [{
                    value: 0,
                    width: 1,
                    color: \'#808080\'
                }]
            },
            tooltip: {
                valueSuffix: \'%\'
            },
            legend: {
                layout: \'vertical\',
                align: \'right\',
                verticalAlign: \'top\',
                x: -10,
                y: 100,
                borderWidth: 0
            },
            series: '.$for_js_series.'
        });
	});
	</script>';
	echo '<div id="container" style="min-width: 400px; height: 400px; margin: 0 auto"></div>';
}

function show_table($group){
	$q="SELECT `name` FROM `tbl_group` where `id`=$group;";
	$WR = fetch($q);
	$group_name = $WR[0];
	
	$q="SELECT `id`, `name` FROM `tbl_criteria` order by  `order` ASC;";
	$r=mysql_query($q);
	if ($r and mysql_num_rows($r)){
		//echo '<h1>SSSSSSSSS</h1>';
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
				echo '<td>';
				echo get_group_percent($group, $w['id'], $xw['num']);
				echo '</td>';
			}
			echo '<td>';
			echo get_group_percent_max($group, $w['id'], $xw['num']);
			echo '</td>';
			echo '</tr>';
		}
		
		echo '<td>&nbsp;</td>';
		echo '<td>ИТОГО %</td>';
		foreach($FETCHARR as $xw){
				echo '<td>';
				echo get_group_percent_all($group, $xw['num']);
				echo '</td>';
		}
		echo '<td>';
		echo '</td>';
		echo '</table>';
		
	}
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
			    <th>&nbsp;</th>
			</tr>";
	while ($w=mysql_fetch_array($r)){
		$id=$w['id'];
		$name=$w['name'];
		$head=$w['head'];
		$table_link ='index.php?action=table&id='.$id;
		$diagram_link ='index.php?action=diagram&id='.$id;
		$table_link = '<a href="'.$table_link.'">Таблица</a>';
		$diagram_link = '<a href="'.$diagram_link.'">Диаграмма</a>';
		echo  "<tr>";
			echo  '<td>'.$name.'</td>';
			echo  '<td>'.$head.'</td>';
			echo  '<td>'.$table_link.'</td>';
			echo  '<td>'.$diagram_link.'</td>';
		echo  "</tr>";
	}

	print "</table>";
}
}



//print '<table width="100%" border="0" cellspacing="0" cellpadding="0">  <tr>    <td><br>';
	
/////////////////////////////// E D I T A B L E /////////////////////////////////////////



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


	
/////////////////////////////// E D I T A B L E /////////////////////////////////////////	
	
//	print'</td></tr></table>';





?>


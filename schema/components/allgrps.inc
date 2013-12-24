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



function get_group_midle($timenum){

	$q = "SELECT `id` FROM `tbl_group` WHERE `deleted`=0;";
	$r=mysql_query($q);
	$SS = 0;
	$p = 0;
	if($r and mysql_num_rows($r)){
		while($w=mysql_fetch_row($r)){
			$SS+=floatval(get_group_percent_all($w[0], $timenum));
			$p++;
		}
	}
	return round($SS/$p,2)."%";
}

function _get_group_midle($timenum){
	$q = "SELECT SUM(`done`) FROM `tbl_donejob` WHERE `timeline_num` = $timenum ;";
	$WR = fetch($q);
	if($WR!==FALSE){
		$sum=$WR[0];
	}
	
	$q = "SELECT count(`id`)  FROM `tbl_donejob` WHERE `timeline_num` = $timenum ;";
	if($WR!==FALSE){
		$cnt=$wr[0];
	}else{
		$cnt=1;
	}
	
	$cnt=($cnt==0)?1:$cnt;
	$pc = round(($sum/$cnt),2);
	return $pc."%";
}


function show_table(){
	$q="SELECT `id`, `name`, `head` FROM `tbl_group` WHERE `deleted`=0 order by  `id` ASC;";
	$r=mysql_query($q);
	if ($r and mysql_num_rows($r)){
		echo '<table width="1000" border="1" cellspacing="0" cellpadding="0" class="table table-bordered table-striped">';
		echo '<tr>
			<td>&nbsp;</td>
			<td>&nbsp;</td>
			<td colspan="4" align="center"><strong>30 июня</strong></td>
			<td colspan="4" align="center"><strong>1 июля</strong></td>
			<td colspan="4" align="center"><strong>2 июля</strong></td>
		  </tr>
		  <tr>
			<td>#</td>
			<td><strong>Группы</strong></td>
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
			$group_id=$w['id'];
			foreach($FETCHARR as $xw){
				echo '<td>';
				echo get_group_percent_all($group_id, $xw['num']);
				echo '</td>';
			}
			echo '<td>';
			echo get_group_percent_all_max($group_id);
			echo '</td>';
			
			echo '</tr>';
		}
		
		echo '<td>&nbsp;</td>';
		echo '<td>ИТОГО %</td>';
		foreach($FETCHARR as $xw){
				echo '<td>';
				echo get_group_midle($xw['num']);
				echo '</td>';
		}
		echo '<td>';
		echo '</td>';
		echo '</table>';
		
	}
}


function show_diagram(){
	
	
	
	
	$for_js_categories=get_categories();
	$for_js_series=get_series_all();
	
	echo '<script>
	$(function () {
        $(\'#container\').highcharts({
            chart: {
                type: \'line\',
                marginRight: 130,
                marginBottom: 25
            },
            title: {
                text: \'Сводная диаграмма\',
                x: -20 //center
            },
            subtitle: {
                text: \'Все группы\',
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


function show_diagram_rectangle(){

	$for_js_groups = get_groups();
	$for_js_series = get_series_all_rectangle();
	echo '<script>
	$(function () {
        $(\'#container2\').highcharts({
            chart: {
                type: \'column\',
                margin: [ 50, 50, 100, 80]
            },
            title: {
                text: \'Сводная диаграмма\',
                x: -20 //center
            },
            subtitle: {
                text: \'Успеваемость\',
                x: -20
            },
            xAxis: {
                categories: ['.$for_js_groups.']
            },
            yAxis: {
                min: 0,
				title: {
                    text: \'Выполненно %\'
                }
            },
            legend: {
                enabled: false
            },
            tooltip: {
                valueSuffix: \'%\'
            },
            series: [{
                name: \'Выполненно\',
                data: ['.$for_js_series.'],
                dataLabels: {
                    enabled: true,
                    rotation: -90,
                    color: \'#FFFFFF\',
                    align: \'right\',
                    x: 4,
                    y: 10,
                    style: {
                        fontSize: \'13px\',
                        fontFamily: \'Verdana, sans-serif\'
                    }
                }
            }]
        });
    });
	</script>';
	echo '<div id="container2" style="min-width: 400px; height: 400px; margin: 0 auto"></div>';
}



function show_list(){
		echo '<div>';
		show_diagram_rectangle();
		echo '</div>';
		echo '<div>';
		show_diagram();
		echo '</div>';
		echo '<br>';
		echo '<div>';
		show_table();
		echo '</div>';
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


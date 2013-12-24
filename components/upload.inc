<?

include("client_ns.php");


/*
echo get_name("04. Charles Bradley & Menahan Street Band - How Long.mp3");
print "<pre>\n POST:";
print_r($_POST);
print "\n  GET:";
print_r($_GET);
print "\n  FILES:";
print_r($_FILES);
print "</pre>";
*/



function delete_file($id){

				$q="select `name`,`path` FROM `file` where `id`=$id;";
				$r=mysql_query($q);
				$w=mysql_fetch_assoc($r);
				$dell_file=$w['name'];
				$ffd=$w['path'];
				if (file_exists($ffd)){
				if( unlink($ffd)){
					errcap("Файл $dell_file был удален!!",'g');
					return true;
				} else {
					errcap("Удаления Файла $dell_file завершилась неудачей, удалите вручную!!", 'r');
					return false;
				}
				} else {
				
					return true;
				
				}
}



function form_adit($m,$cnt){
if($m=="add"){
$but ="Добавить";
$cap="Добавления файлов:";
$name =    "";
$comment = "";
$hide_sector="<input type=\"hidden\" name=\"action\"  value=\"save\" />
		      <input type=\"hidden\" name=\"sact\"  value=\"add\" />";

$replacement="";
}else{ 
$but = "Сохранить";
$cap="Изминения файлов:";
$name =    $cnt['name'];
$comment=  $cnt['comment'];
$id = $cnt['id'];

$hide_sector="<input type=\"hidden\" name=\"action\"  value=\"save\" />
			<input type=\"hidden\" name=\"sact\"  value=\"update\" />
			  <input type=\"hidden\" name=\"id\"  value=\"$id\" />";
			  
$replacement="<span >Заминить</span><input name=\"doreplace\" id=\"doreplace\" type=\"checkbox\" checked  />";
}



print "<table width=\"600px\" border=\"0\" cellspacing=\"0\" cellpadding=\"0\" align=\"center\" class=\"table table-bordered table-striped\">
 <form id=\"form1\" name=\"form1\" method=\"post\" action=\"".$PHP_SELF."\" onsubmit=\"return login_submit();\" enctype=\"multipart/form-data\">
  $hide_sector
  <tr>
    <th align\"right\" >Названия&nbsp;&nbsp;</th>
    <td >
       <input name=\"name\" type=\"text\" class=\"navLink\" id=\"fio\"  value=\"$name\"/>    </td>
  </tr>
  <tr>
    <th align\"right\" >&nbsp;Коментария&nbsp;&nbsp;</th>
    <td ><textarea name=\"comment\" cols=\"40\" rows=\"5\" class=\"navLink\" id=\"vcomment\">$comment</textarea></td>
  </tr>
  <tr>
    <th align\"right\" > &nbsp;Файл&nbsp;&nbsp;</th>
    <td  nowrap=\"nowrap\">
        <span >Загрузить</span>
      <input name=\"doupload\" id=\"doupload\" type=\"checkbox\"  />  
	  <input name=\"upload_file\"  type=\"file\" class=\"navLink\" id=\"upload_file\"  value=\"\" />
			$replacement
   </td>
  </tr>
  <tr>
    <td colspan=\"2\" align=\"center\" >
        <input name=\"button\" type=\"submit\" class=\"btn\" value=\"$but\" />
     </td>
    </tr>
  </form>
</table>";

}


function show_list(){
global $cur;

$q="SELECT `id`, `name`, `path`, `ddate`, `count`, `comment` FROM `file` order by `name` ASC";
$r=mysql_query($q);
if ($r){
	$count = mysql_num_rows($r);
	//width=\"90%\"
	print "<table  align=\"center\" border=\"0\" cellspacing=\"0\" cellpadding=\"0\" class=\"table table-bordered table-striped\">
			  <tr>
			    <td  colspan=6>
				<form action=\"".$PHP_SELF."\" method=\"post\">
				<input name=\"action\" type=\"hidden\" value=\"add\" />
				<input name=\"submit\" class=\"btn\" type=\"submit\" value=\"Добавить\" />
				</form>
				</td>
			    
			</tr>
			<tr>
			    <th>Названия</th>
				<th>Путь</th>
				<th>Описания</th>
				<th>Дата добавления</th>
				<th>Изменить</th>
			    <th>Удалить</th>
			</tr>";
	while ($w=mysql_fetch_array($r)){
		$id=$w[id];
		$name=(is_null($w['name']) || $w['name']=="")?"No Name":$w['name'];
		$path=$w['path'];
		$comm=(is_null($w['comment']) || $w['comment']=="")?"No Comment":$w['comment'];
			
		$ad=$w['ddate'];
		
		print "<tr>
				  <form action=\"".$PHP_SELF."\" method=\"post\" >
					<input type=\"hidden\" name=\"action\" value=\"flist\" />
					<input type=\"hidden\" name=\"id\" value=\"$id\" />
				    <td >$name</td>
					<td >$path</td>
					<td >$comm</td>
					<td >$ad</td>
				    <td  align=\"center\">
				        <input type=\"submit\" class=\"btn\"  name=\"edit\" value=\"Редактировать\" />
				    </td>
				    <td  align=\"center\">
				        <input type=\"submit\" class=\"btn\" name=\"delete\" value=\"Удалить\" />
				    </td>
					</form>
				<tr>";
	}

	print "<tr>
		    <th  colspan=6>Количество $count штук</th>
		</tr>
		</table>";
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
		case "add":
		{
			form_adit("add","");
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


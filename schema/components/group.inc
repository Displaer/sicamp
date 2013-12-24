<?

if(isset($_SESSION['fuser'])){

function form_adit($m,$cnt){
if($m=="add"){
$but ="Добавить";
$cap="Добавления группы:";
$name =  "";
$head = "";
$hide_sector="<input type=\"hidden\" name=\"action\"  value=\"save\" />
		      <input type=\"hidden\" name=\"sact\"  value=\"add\" />";

}else{ 
$but = "Сохранить";
$cap="Изминения группы:";
$id = $cnt['id'];
$name =    $cnt['name'];
$head=  $cnt['head'];
$hide_sector="<input type=\"hidden\" name=\"action\"  value=\"save\" />
			<input type=\"hidden\" name=\"sact\"  value=\"update\" />
			  <input type=\"hidden\" name=\"id\"  value=\"$id\" />";
			  
}

print "<table width=\"600px\" border=\"0\" cellspacing=\"0\" cellpadding=\"0\" align=\"center\" class=\"table table-bordered table-striped\">
 <form id=\"form1\" name=\"form1\" method=\"post\" action=\"".$PHP_SELF."\" onsubmit=\"return login_submit();\" enctype=\"multipart/form-data\">
  $hide_sector
  <tr>
    <th align\"right\" >Названия:</th>
    <td >
       <input name=\"name\" type=\"text\" class=\"navLink\"  value=\"$name\"/>    
	</td>
  </tr>
  <tr>
    <th align\"right\" >Проект:</th>
    <td>
       <input name=\"head\" type=\"text\" class=\"navLink\"  value=\"$head\"/>    
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

$q="SELECT `id`, `name`, `head` FROM `tbl_group` WHERE `deleted`=0 ORDER BY `id` ASC";
$r=mysql_query($q);
if ($r){
	$count = mysql_num_rows($r);
	//width=\"90%\"
	print "<table  align=\"center\" border=\"0\" cellspacing=\"0\" cellpadding=\"0\" class=\"table table-bordered table-hover\">
			  <tr>
			    <td  colspan=4>
				<form action=\"".$PHP_SELF."\" method=\"post\">
				<input name=\"action\" type=\"hidden\" value=\"add\" />
				<input name=\"submit\" class=\"btn\" type=\"submit\" value=\"Добавить\" />
				</form>
				</td>
			    
			</tr>
			<tr>
			    <th>Названия</th>
				<th>Проект</th>
				<th>Изменить</th>
			    <th>Удалить</th>
			</tr>";
	while ($w=mysql_fetch_array($r)){
		$id=$w['id'];
		$name=(is_null($w['name']) || $w['name']=="")?"No Name":$w['name'];
		$head=(is_null($w['head']) || $w['head']=="")?"No Head":$w['head'];
		print "<tr>
				  <form action=\"".$PHP_SELF."\" method=\"post\" >
					<input type=\"hidden\" name=\"action\" value=\"flist\" />
					<input type=\"hidden\" name=\"id\" value=\"$id\" />
				    <td >$name</td>
					<td >$head</td>
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
		    <th  colspan=6>Количество: $count</th>
		</tr>
		</table>";
}else echo mysql_error();
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
				$q="SELECT * FROM `tbl_group`  where `id`=$id;";
				$r=mysql_query($q);
				if ($r && mysql_num_rows($r)>0){
					$w=mysql_fetch_assoc($r);
					form_adit("edit",$w);
				}
			
			
			} elseif(isset($_POST['delete'])){
				$id=$_POST['id'];
				$q="UPDATE `tbl_group` SET `deleted`=1 WHERE `id`=$id LIMIT 1;";
				$r=mysql_query($q);
				if ($r){
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
			
			$sact=$_POST['sact'];
			$name=$_POST['name'];
			$head=$_POST['head'];
			
			if ($sact=="add"){
				$q="INSERT INTO `tbl_group` (`id`, `name`, `head`, `deleted`) VALUES (NULL, '$name', '$head', 0);";
				if (mysql_query($q)){
					errcap('Запись добавлено успещно','g');
				} else {
					errcap('Запись добавить не удалось','r');
				}
			}elseif($sact=="update"){
				$id=$_POST['id'];
				$q="UPDATE `tbl_group` SET 
					 `name` = '$name',
					 `head` = '$head'
					  WHERE `id` =$id LIMIT 1;";
				if (mysql_query($q)){
					errcap('Запись обновлено успещно.','g');
				} else {
					errcap('Запись обновить не удалось','r');
				}
			} 
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
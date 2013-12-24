<?php
if(isset($_SESSION['fuser'])){
	echo '<div class="center"><h1>WLCOME ADMINISTRATOR!</h1></div>';
echo'<p>';
echo'<ul>';
echo'<li><a href="?control=group">Группы</a>';
echo'<li><a href="?control=data">Ввод данных</a>';
echo'</ul>';
echo'</p>';


}else{
	echo '<div class="center"><h1>WLCOME TO SICAMP 2013!</h1></div>';
}

?>
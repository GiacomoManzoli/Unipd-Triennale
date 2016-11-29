<?php
session_start();
require_once('./support/_components.php');
require_once('./support/_various.php');

$disegnaPagina = true;

if (isset($_SESSION["username"]) &&$_SESSION["username"]!=""){
	header("Location: index.php");
}
else{
	$_SESSION["username"]="";
}

if ($_POST["username"]!=""){
	//echo $_POST["username"]." ".$_POST["password"];
	$disegnaPagina = !login($_POST["username"],$_POST["password"]);
}

if ($disegnaPagina){
	startPage("Login",0);
	drawLogo();

	echo '<div class="row"><div class="col-md-4 col-md-offset-4">';
	echo '<form class="form" method="POST" action="'.baseUrl().'/login.php">';

	echo '<div class="form-group">';
	echo '<label for="username">Username</label>';
	echo '<input type="text" class="form-control" id="username" name="username">';
	echo '</div>';

	echo '<div class="form-group">';
	echo '<label for="username">Password</label>';
	echo '<input type="password" class="form-control" id="password" name="password">';
	echo '</div>';

	echo '<input type="submit" class="btn btn-primary" value="Accedi"/>';
	echo '   Non hai un utente? <a href="'.baseUrl().'/registrazione.php">Registrati</a>';
	echo '</form>';
	echo '</div></div>';



	endPage();
}
?>

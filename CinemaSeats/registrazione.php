<?php
require_once('./support/_components.php');
require_once('./support/_database.php');
require_once('./support/_various.php');

session_start();
$disegnaPagina = true;


if ($_SESSION["username"]!=""){ // controllo che l'utente non sia già loggato.
	$disegnaPagina = false;
	header("location: index.php");	
}

if ($_POST["isPostBack"]){
	$err=false;
	if (trim($_POST["username"])==""){
		$_SESSION["ERROR_MSG"][]="Il campo nome utente non puo' essere vuoto";
		$err=true;
	}
	if (trim($_POST["password"])==""){
		$_SESSION["ERROR_MSG"][]="Il campo password non puo' essere vuoto";
		$err=true;
	}
	if ($_POST["email"]==""){
		$_SESSION["ERROR_MSG"][]="Il campo email non puo' essere vuoto";
		$err=true;
	}
	if (!$err) {
		$username = $_POST["username"];
		$password = $_POST["password"];
		$email = $_POST["email"];

		connect($dbcon);
		$query = "call inserisciCliente('$username','$password','$email')";
		mysql_query($query);
		if (mysql_errno()==1062){
			$_SESSION["ERROR_MSG"][] = "Nome utente o email gia' in uso";
		}
		else{
			$disegnaPagina = !login($username,$password);
		}
	}	
}


if ($disegnaPagina){

	startPage("Registrazione",0);
	drawLogo(); //disegna anche i messaggi d'errore

	echo '<div class="row"><div class="col-md-4 col-md-offset-4">';
	echo '<form class="form" method="POST" action="'.baseUrl().'/registrazione.php">';

	echo '<div class="form-group">';
	echo '<label for="username">Username</label>';
	echo '<input type="text" class="form-control" id="username" name="username" value="'.$_POST["username"].'">';
	echo '</div>';

	echo '<div class="form-group">';
	echo '<label for="username">Password</label>';
	echo '<input type="password" class="form-control" id="password" name="password" value="'.$_POST["password"].'">';
	echo '</div>';

	echo '<div class="form-group">';
	echo '<label for="email">E-mail</label>';
	echo '<input type="email" class="form-control" id="email" name="email" value="'.$_POST["email"].'">';
	echo '</div>';

	echo '<input type="hidden" name="isPostBack" value="true"/>';
	echo '<input type="submit" class="btn btn-primary" value="Registrati"/>';
	echo '   Hai gia\' un utente? <a href="'.baseUrl().'/login.php">Accedi</a>';
	echo '</form>';
	echo '</div></div>';

	endPage();
}
?>
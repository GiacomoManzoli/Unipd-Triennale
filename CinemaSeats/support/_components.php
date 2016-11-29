<?php

require_once('./support/_various.php');

function startPage($titolo,$auth){
	if(session_id() == '') 
		session_start();
	$isAuth=verifyAuth($auth);
		echo '<!DOCTYPE html>
		<html>
		<head>
			<title>'.$titolo.' </title>
			<link href="css/bootstrap.css" rel="stylesheet" type="text/css" />
			<link href="css/custom.css" rel="stylesheet" type="text/css" />
		</head>

		<body>

		<div class = "container">';
	return $isAuth;
} 

function endPage() {
	echo '</div></body></html>';
}

function drawMessages(){

	if (isset($_SESSION["ERROR_MSG"])){
		drawMsgs("danger",$_SESSION["ERROR_MSG"]);
	}
	if (isset($_SESSION["SUCCESS_MSG"])){
		drawMsgs("success",$_SESSION["SUCCESS_MSG"]);		
	}
	$_SESSION["ERROR_MSG"]=array();
	$_SESSION["SUCCESS_MSG"]=array();
}

function drawMsgs($level,$msgs){
	if (isset($msgs) && count($msgs)>0){
		echo "<div class=\"alert alert-$level\"><ul>";
		foreach ($msgs as $msg) {
			echo "<li>$msg</li>";
		}
		echo '</ul></div>';
	}
}

function drawMsg($level,$msg){
	echo "<div class=\"alert alert-$level\">";
	echo "$msg";
	echo '</div>';
}

function drawLogo(){
	echo '<div class = "jumbotron">
	<a href="'.baseUrl().'/index.php"><h1>CineEuroMultiPlex</h1></a>
	<p>Il vero cinema, solo da noi!</p>
	</div>';
	drawMessages();
}

function drawUserBar($forPage){
	if (isset($_SESSION["auth_level"]))
		$level = $_SESSION["auth_level"];
	else 
		$level = 0;
	$a0="";$a1="";$a2="";$a3="";$a4="";
	switch ($forPage) {
		case 0: $a0 ="class=\"active\""; break;
		case 1: $a1 ="class=\"active\""; break;
		case 2: $a2 ="class=\"active\""; break;
		case 3: $a3 ="class=\"active\""; break;
		case 4: $a4 ="class=\"active\""; break;
	}

	echo "<div class=\"row\"><div class=\"col-md-12\">";
	if ($level>0) {
		echo "<ul class=\"nav nav-tabs\">";
	  	echo "<li $a0><a href=\"".baseUrl()."/index.php\">Proiezioni</a></li>";
	  	echo "<li $a1><a href=\"".baseUrl()."/prenota.php\">Prenota</a></li>";
	  	echo "<li $a2><a href=\"".baseUrl()."/profilo.php\">Le Mie Prenotazioni</a></li>";

	  	if ($level > 1)
	  		echo "<li $a3><a href=\"".baseUrl()."/cercaPrenotazioni.php\">Cerca Prenotazioni</a></li>";
	  	if ($level > 2)
	  		echo "<li $a4><a href=\"".baseUrl()."/admin.php\">Amministrazione</a></li>";
		echo "</ul>";
		
	}
	echo "</div></div>";
	echo "<div class=\"row\"><div class=\"col-md-12\">";
	echo '<div class="pull-right">';
	if (isset($_SESSION["username"]))
		$username =$_SESSION["username"];
	else 
		$username="";
	if ($username!=""){	
		echo '<form method="POST" action="'.baseUrl().'/logout.php">';
		echo "Sei loggato come $username ";
		echo '<input type="submit" class="btn btn-danger" value="Log out">';
		echo '</form>';
	}
	else{
		echo '<a href="'.baseUrl().'/login.php"><button type="button" class="btn btn-primary">Accedi</button></a> ';
		echo '<a href="'.baseUrl().'/registrazione.php"><button type="button" class="btn btn-default">Registrati</button></a>';
	}
	echo '</div>';
	echo "</div></div>";
	
}

function drawAdminBar($forPanel){
	$a0="";$a1="";$a2="";$a3="";$a4="";
	switch ($forPanel) {
		case 0: $a0 ="class=\"active\""; break; //Recap
		case 1: $a1 ="class=\"active\""; break;	//Proiezioni
		case 2: $a2 ="class=\"active\""; break; //Staff
		case 3: $a3 ="class=\"active\""; break; //Film
		case 4: $a4 ="class=\"active\""; break; //Sale
	}
	echo '<div class="row"><div class ="col-md-12">';
	echo '<h2>Pannello di Amministrazione</h2>';
	echo '</div></div>';
	echo "<div class=\"row\"><div class=\"col-md-12\">";
	echo "<ul class=\"nav nav-pills\">";
	  	echo "<li $a0><a href=\"".baseUrl()."/admin.php\">Start</a></li>";
	  	echo "<li $a1><a href=\"".baseUrl()."/admin_spett.php\">Proiezioni</a></li>";
	  	echo "<li $a2><a href=\"".baseUrl()."/admin_staff.php\">Staff</a></li>";
	  	echo "<li $a3><a href=\"".baseUrl()."/admin_film.php\">Film</a></li>";
	  	echo "<li $a4><a href=\"".baseUrl()."/admin_sale.php\">Sale</a></li>";
	echo "</ul>";
	echo "</div></div>";
}

function drawFilm($datiFilm){
	$titolo = $datiFilm[1];
	$desc = $datiFilm[2];
	
	$urlLocandina=$datiFilm[3];
	$durata=$datiFilm[4];

	$proiezioni = $datiFilm[5];


	echo '<div class="row">';
	echo '<div class="col-md-2">';
	echo "<img src=\"$urlLocandina\" alt=\"Locandina $titolo\" class = \"img-rounded locandina\"/>";
	echo '</div>';

	echo '<div class="col-md-10">';
	echo "<h2>$titolo</h2>";
	echo "<p><strong>Durata:</strong> $durata</p>";
	echo "<strong>Proiezioni:</strong>";
	echo '<ul class="list-group">';
	foreach ($proiezioni as $data => $ora) {
		echo "<li class=\"list-group-item\"><strong>$data</strong> $ora</li>";
	}
	echo '</ul>';
	echo "<strong>Trama:</strong>";
	echo "<div class=\"film-desc \">";
	echo "<p>$desc</p>";
	echo '</div>';
	echo '</div>';

	echo '</div>'; #fine ROW
}

function drawStartTable($header){
	echo '<table class = "table table-striped">';
	echo '<thead><tr>';
	foreach ($header as $value) {
		echo "<th>$value</th>";
	}
	echo '</tr></thead><tbody>';
}

function drawTableRow($row){
	echo '<tr>';
	foreach ($row as $value) {
		echo "<td>$value</td>";
	}
	echo '</tr>';
}

function drawEndTable(){
	echo '</tbody></table>';
}

function drawStartForm($action,$css=""){
	echo "<form method=\"POST\" 
				action=\"".baseUrl()."$action\" 
				class=\"$css\" 
				role=\"form\">";

}
function drawEndForm(){
	echo '</form>'; 
}
function drawFormField($type,$id,$desc="",$default="",$css="",$extraAtt=""){
	echo '<div class="form-group">';
	echo "<label 	for=\"$id\" 
					class=\"col-sm-2 control-label\">$desc</label>";
	echo "	<div class=\"col-sm-10\">
			<input 	type=\"$type\" 
					class=\"form-control $css\" 
					id=\"$id\" 
					name=\"$id\" 
					value=\"$default\"
					 $extraAtt></div>";
	echo '</div>';
}

function drawHiddenField($id,$value){
	echo '<input type="hidden" id="'.$id.'" name="'.$id.'" value="'.$value.'"/>';
}

?>

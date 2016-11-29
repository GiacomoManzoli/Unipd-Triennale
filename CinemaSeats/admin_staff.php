<?php
require_once('./support/_components.php');
require_once('./support/_database.php');
require_once('./support/_various.php');


$autorizzato = startPage("Amministrazione - Staff",3);


if ($autorizzato){
	connect($dbcon);
	if ($_POST["action"]=="insert"){
		$_username = trim($_POST["username"]);
		$_password = trim($_POST["password"]);
		$_confermaPassword =trim($_POST["confermaPassword"]);
		$_nome = $_POST["nome"];
		$_cognome = $_POST["cognome"];
		$_ruolo = $_POST["ruolo"];
		$err =false;
		if ($_username ==""){
			$_SESSION["ERROR_MSG"][]="Il campo username non puo' essere vuoto";
			$err=true;
		}
		if ($_password ==""){
			$_SESSION["ERROR_MSG"][]="Il campo password non puo' essere vuoto";
			$err=true;
		}
		if ($_confermaPassword==""){
			$_SESSION["ERROR_MSG"][]="Il campo conferma password non puo' essere vuoto";
			$err=true;
		}
		if ($_confermaPassword!=$_password){
			$_SESSION["ERROR_MSG"][]="Le due password sono diverse";
			$err=true;
		}
		if ($_nome==""){
			$_SESSION["ERROR_MSG"][]="Il campo nome  non puo' essere vuoto";
			$err=true;
		}
		if ($_cognome ==""){
			$_SESSION["ERROR_MSG"][]="Il campo cognome non puo' essere vuoto";
			$err=true;
		}
		if ($_ruolo==""){
			$_SESSION["ERROR_MSG"][]="E' necessario selezionare un ruolo";
			$err=true;
		}
		if (!$err){
			$query = "call inserisciStaff('$_username','$_password','$_nome','$_cognome','$_ruolo')";
			mysql_query($query);
			if (mysql_errno()==1062){
				$_SESSION["ERROR_MSG"][] = "Username gia' in uso";
			}else{
				$_SESSION["SUCCESS_MSG"][] ="Utente inserito con successo";
				$_username="";
				$_password="";
				$_nome="";
				$_cognome="";
			}
		}
	}
	if ($_POST["action"]=="delete"){
		$username = mysql_real_escape_string($_POST["username"]);
		$query = "delete from utenti where username='$username'";
		mysql_query($query);
		if (mysql_error()==""){
			$_SESSION["SUCCESS_MSG"][] = "L'utente $username e' stato cancellato";
		}
		else{
			$_SESSION["ERROR_MSG"][] ="Si è verificato un problema e l'utente non è stato cancellato";
		}
	}

	drawLogo();
	drawUserBar(4);
	drawAdminBar(2);

	echo '<div class="row"><div class ="col-md-12">';
	echo '<h3>Gestione personale</h3>';

	echo '<h4>Inserisci</h4>';
	drawStartForm("/admin_staff.php","form-horizontal");

	drawFormField("text","username","Username",$_username);
	drawFormField("password","password","Password");
	drawFormField("password","confermaPassword","Conferma Password");
	drawFormField("text","nome","Nome",$_nome);
	drawFormField("text","cognome","Cognome",$_cognome);

	echo '<div class="form-group">';
	echo "<label 	for=\"ruolo\" 
					class=\"col-sm-2 control-label\">Ruolo</label>";
	echo '<div class="col-sm-10"><select name = "ruolo" class=" col-sm-4 form-control">
			<option>Commesso</option>
			<option>Admin</option>
			</select></div>';

	echo '</div>';


	drawFormField("submit","","","Inserisci");
	drawHiddenField("action","insert");
	drawEndForm();

	$query = "select * from Utenti natural join Staff order by cognome, nome";
	$ris = mysql_query($query);

	echo '<h4>Lista personale</h4>';
	drawStartTable(array("Username","Nome","Cognome","Ruolo","Azioni"));
	while ($row = mysql_fetch_row($ris)) {
		$login = $row[0];
		$nome = $row[2];
		$cognome = $row[3];
		$ruolo = $row[4];

		$js=" return confirm('Cancellando $login verranno perse tutte le prenotazioni da lui effettuate. Continuare?')";
		$formPerCancellazione ='<form method="POST" action = "'.baseUrl().'/admin_staff.php"">
								<input type="submit" value="Cancella" onClick="'.$js.'" value="Cancella" class="btn btn-danger btn-xs">
								<input type="hidden" name ="action" value="delete"/>
								<input type="hidden" name ="isPostBack" value="true"/>
								<input type="hidden" name ="username" value="'.$row[0].'"/>
								</form>';
		
		
		drawTableRow(array($login,$nome,$cognome,$ruolo,$formPerCancellazione));
	}
	drawEndTable();
}
endPage();

?>
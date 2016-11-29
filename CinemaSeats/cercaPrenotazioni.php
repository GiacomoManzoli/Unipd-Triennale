<?php
require('./support/_database.php');
require('./support/_components.php');
require_once('./support/_various.php');


$autorizzato = startPage("Cerca prenotazioni",2);

if ($autorizzato){
	connect($dbcon);
	$username=$_POST["username"];

	if ($_POST["isPostBack"]){
		
		$codicePrenotazione = $_POST["codicePrenotazione"];
		if ($_POST["ritirata"]==1){
			$query ="update Prenotazioni set ritirata = '1' where codicePrenotazione=$codicePrenotazione";
			mysql_query($query);
			if (mysql_error()=="")
				$_SESSION["SUCCESS_MSG"][] = "Prenotazione $codicePrenotazione marcata come ritirata";
			else 
				$_SESSION["ERROR_MSG"][] = "Si e' verificato un problema";
		}
	}

	drawLogo();
	drawUserbar(3);


	echo '<h2>Ricerca prenotazioni</h2>';

	echo '<form class="form-inline" role="form" method="POST" action="'.baseUrl().'/cercaPrenotazioni.php">';
	echo '<div class="form-group">';
	echo '<label for="username">Username: </label>';
	echo '<input type="text" class="form-control" id="username" name="username" value='.$username.'>';
	echo '</div>'; 
	echo '<input type="submit" class="btn btn-default" value="Cerca"/>';
	echo '</form>';


	$query="select codicePrenotazione,(ritirata+0),proiezione,utente from Prenotazioni where". (($username!="")?" utente like '%$username%' and ritirata='0' order by utente":" false");	
	$res= mysql_query($query);
	if ($username != ""){
		if (mysql_num_rows($res) == 0){
			echo '<br>';
			drawMsg("warning",'Non è stata trovata alcuna prenotazione da ritirare');
		}
		else{

			$tableHeader = array("Codice","Username","Film","Data","Costo","Ritirata","Posti");
			drawStartTable($tableHeader);
			while ($row = mysql_fetch_row($res)){
				$codicePren = $row[0];
				$ritirata = $row[1]==1;
				$codiceProiezione=$row[2];
				$utente=$row[3];
				$query = "select titolo, DATE_FORMAT(data,'%e/%c/%Y'), TIME_FORMAT(ora,'%k:%i'), costoPerPosto from Proiezioni join Film on (film = codiceFilm) where codiceProiezione=$codiceProiezione";
				
				$ris = mysql_query($query);
				$dati = mysql_fetch_row($ris);
				$titolo = $dati[0];
				$data = $dati[1];
				$ora = $dati[2];
				$costoPerPosto = $dati[3];

				$query = "select codicePosto, fila, numero from Posti natural join PostiPrenotati where codicePrenotazione='$codicePren'";
				$ris = mysql_query($query);
				$numPosti = mysql_num_rows($ris);	
				while ($posto = mysql_fetch_row($ris)){
					$posti[] = $posto[1]."-".$posto[2];
				}
				$checkbox="";
				if ($ritirata){
					$checkbox ="disabled checked";
				}
				$formRitirata = '	<form action="'.baseUrl().'/cercaPrenotazioni.php" method="POST" class="form-inline">
									<input type="checkbox" name="ritirata" value="1" onChange="submit()" '.$checkbox.'>
									<input type="hidden" name="codicePrenotazione" value="'.$codicePren.'">
									<input type="hidden" name="username" value="'.$username.'">
									<input type="hidden" name="isPostBack" value="true">
									</form>';

				$colonne=array($codicePren,$utente, $titolo, $data." ".$ora, ($costoPerPosto*$numPosti)." Euro",$formRitirata,implode(" ", $posti));
				drawTableRow($colonne);
				unset($posti);
			}
			drawEndTable();
		}
	}
}
endPage();
?>

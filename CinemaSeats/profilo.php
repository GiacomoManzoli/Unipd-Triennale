<?php
require_once('./support/_database.php');
require_once('./support/_components.php');
require_once('./support/_various.php');

$autorizzato = startPage("Le mie prenotazioni",1);
if ($autorizzato){
	connect($dbcon);
	$currentUser=$_SESSION["username"];

	if ($_POST["action"]=="delete_pren"){
		$codicePrenotazione = $_POST["codicePrenotazione"]*1;
		if ($codicePrenotazione>0){
			$query = "delete from Prenotazioni where codicePrenotazione = $codicePrenotazione";
			mysql_query($query);
			if (mysql_error()==""){
				$_SESSION["SUCCESS_MSG"][] = "Prentoazione $codicePrenotazione cancellata!";
			}else{
				$_SESSION["ERROR_MSG"][] ="Non è stato possibile cancellare la prenotazione";
			}
		}else{
			$_SESSION["ERROR_MSG"][] ="Codice prenotazione non valido";
		}

	}
	if ($_POST["action"]=="delete_posto"){
		$codicePosto=$_POST["codicePosto"]*1;
		$codicePrenotazione = $_POST["codicePrenotazione"]*1;
		if ($codicePosto>0 && $codicePrenotazione>0){
			$query ="delete from PostiPrenotati where codicePrenotazione=$codicePrenotazione and codicePosto=$codicePosto";
			mysql_query($query);
			if (mysql_error()==""){
				$_SESSION["SUCCESS_MSG"][] = "Posto cancellato!";
			}else{
				$_SESSION["ERROR_MSG"][] ="Non è stato possibile rimuovere il posto dalla prenotazione";
			}
		}
	}
	drawLogo();
	drawUserbar(2);

	echo '<h2>Le mie prenotazioni</h2>';

	$query="select pren.codicePrenotazione,(pren.ritirata+0),pren.proiezione 
			from Prenotazioni pren join Proiezioni proj on (proiezione=codiceProiezione) 
			where utente='$currentUser' and proj.data>=now()";
	$res=mysql_query($query);

	if (mysql_num_rows($res)==0){
		echo '<div class="alert alert-info"> 
			<p>Non hai ancora effettuato una prenotazione, che cosa aspetti</p>
			<a href="'.baseUrl().'/prenota.php"><button class="btn btn-primary btn-lg">Prenota Ora</button></a></div>';
	}
	else {
		echo '<p>Per cancellare dei posti da una prenotazione ti basta premere il link corrispondente al posto che vuoi cancellare, ti ricordiamo che puoi cancellare solamente i posti esterni di prenotazioni che non sono ancora state ritirate.</p>';
		echo '<p>Per ritirare una prenotazione e\' sufficente presentarsi alle cassa con il proprio username, se una prenotazione non verra\' ritirata almeno un quarto d\'ora prima dell\'inizio dello spettacolo sara\' automaticamente cancellata.</p>';
		$tableHeader = array("Codice","Film","Data","Costo","Ritirata","Posti","Azioni");
		drawStartTable($tableHeader);
		while ($row = mysql_fetch_row($res)){
			$codicePren = $row[0];
			$ritirata = $row[1]==1;
			$codiceProiezione=$row[2];
			$query = "select titolo, DATE_FORMAT(data,'%e/%c/%Y'), TIME_FORMAT(ora,'%k:%i'), costoPerPosto from Proiezioni join Film on (film = codiceFilm) where codiceProiezione=$codiceProiezione";
			
			
			$ris = mysql_query($query);
			$dati = mysql_fetch_row($ris);
			$titolo = $dati[0];
			$data = $dati[1];
			$ora = $dati[2];
			$costoPerPosto = $dati[3];
			
			

			$query = "select codicePosto, fila, numero from Posti natural join PostiPrenotati where codicePrenotazione='$codicePren' order by fila,numero";
			$ris = mysql_query($query);
			$numPosti = mysql_num_rows($ris);
			
			while ($posto = mysql_fetch_row($ris)){
				$posti[] = $posto;
			}

			$statoBottoni = ($ritirata)?"disabled":"";
			// creo il form per il primo posto
			$js ="return confirm('Sei sicuro di voler il posto?');";
			$formPrimoPosto	  ='<form method="POST" action = "'.baseUrl().'/profilo.php" class="form-inline form-posti">
								<input type="submit" value="'.$posti[0][1]."-".$posti[0][2].'" onClick="'.$js.'" class="btn btn-default btn-xs '.$statoBottoni.'">
								<input type="hidden" name ="action" value="delete_posto"/>
								<input type="hidden" name ="codicePosto" value="'.$posti[0][0].'"/>
								<input type="hidden" name ="codicePrenotazione" value="'.$codicePren.'"/>
								</form>';
								
			$ultimoPosto = end($posti);
			$formUltimoPosto="";
			if ($ultimoPosto != $posti[0]){
				$formUltimoPosto =	'<form method="POST" action = "'.baseUrl().'/profilo.php" class="form-inline form-posti">
									<input type="submit" value="'.$ultimoPosto[1]."-".$ultimoPosto[2].'" onClick="'.$js.'" value="Cancella" class="btn btn-default btn-xs '.$statoBottoni.'">
									<input type="hidden" name ="action" value="delete_posto"/>
									<input type="hidden" name ="codicePrenotazione" value="'.$codicePren.'"/>
									<input type="hidden" name ="codicePosto" value="'.$ultimoPosto[0].'"/>
									</form>';
			}
			$stringaPosti = $formPrimoPosto;
			for ($i=1; $i < count($posti)-1; $i++) { 
				$stringaPosti = $stringaPosti.' <button class="btn btn-default btn-xs disabled">'.($posti[$i][1]."-".$posti[$i][2])."</button>";
			}
			
			$stringaPosti = $stringaPosti ." ".$formUltimoPosto;

			//creo il form per cancellare l'intera prenotazione
			$js="return confirm('Sei sicuro di voler cancellare la prenotazione?');";
			$formPerCancellazione ='<form method="POST" action = "'.baseUrl().'/profilo.php">
								<input type="submit" value="Cancella" onClick="'.$js.'" value="Cancella" class="btn btn-danger btn-xs"'.$statoBottoni.'>
								<input type="hidden" name ="action" value="delete_pren"/>
								<input type="hidden" name ="codicePrenotazione" value="'.$codicePren.'"/>
								</form>';

			$colonne=array($codicePren, $titolo, $data." ".$ora, ($costoPerPosto*$numPosti)." Euro",($ritirata)?"Si":"No",$stringaPosti,$formPerCancellazione);

			drawTableRow($colonne);
			unset($posti);
		}

		drawEndTable();
	}
}

endPage();
?>
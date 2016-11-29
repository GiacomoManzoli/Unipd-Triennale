<?php
require_once('./support/_components.php');
require_once('./support/_database.php');
require_once('./support/_various.php');

$autorizzato = startPage("Amministrazione - Proiezioni",3);

if ($autorizzato){
	connect($dbcon);
	if ($_POST["action"]=="insert"){
		$err = false;
		$codiceFilm=$_POST["codiceFilm"];
		$codiceSala=$_POST["codiceSala"];
		$costoPerPosto=$_POST["costoPerPosto"];

		$data = $_POST["data"];
		$ora = $_POST["ora"]; 
		

		if ($codiceFilm == -1){
			$err =true;
			$_SESSION["ERROR_MSG"][] ="Devi selezionare un film";
		}
		if ($codiceSala == -1){
			$err=true;
			$_SESSION["ERROR_MSG"][]="Devi selezionare una sala";
		}
		if ($costoPerPosto <0){
			$err=true;
			$_SESSION["ERROR_MSG"][]="Il costo di un posto non può essere negativo";
		}
		if (!strtotime($data)){
			$err = true;
			$_SESSION["ERROR_MSG"][] = "Data non valida";
		}
		if(!isTime($ora)){
			$err=true;
			$_SESSION["ERROR_MSG"][] = "Ora non valida";
		}
		$dataora = $data." ".$ora;
		$dataNelPassato= $dataora <= date("Y-m-d H:i:s");
		if ($dataNelPassato && !$err){
			$err =true;
			$_SESSION["ERROR_MSG"][] = "Non e' possibile inserire uno spettacolo nel passato"; 
		}

		
		if (!$err){
			if ($costoPerPosto=="") $costoPerPosto=5;
			$query = "insert into Proiezioni values(0,'$data','$ora',$costoPerPosto,$codiceSala,$codiceFilm)";
			mysql_query($query);
			if (mysql_errno()>0){
				$_SESSION["ERROR_MSG"][] = "La sala e' occupata";
				
			}
			else{
				$_SESSION["SUCCESS_MSG"][] ="Proiezione inserita con successo";
				unset($_POST);
			}
		}
	}

	if ($_POST["action"]=="delete"){
		$id = $_POST["codiceProiezione"]*1;
		$query = "delete from Proiezioni where codiceProiezione=$id";
		mysql_query($query);
		if (mysql_errno()==0){
			$_SESSION["SUCCESS_MSG"][] ="Proiezione cancellata";
		}
		else{
			$_SESSION["ERROR_MSG"][] ="Non e' stato possibile cancellare la prenotazione";
		}
	}

	drawLogo();
	drawUserBar(4);
	drawAdminBar(1);

	echo '<div class="row"><div class ="col-md-12">';
	echo '<h3>Inserisci Proiezione</h3>';

	$query = "Select titolo,codiceFilm from Film";
	$result=mysql_query($query);
	$titoliFilm=array();
	$codiciFilm=array();
	while ($row = mysql_fetch_row($result)){
		$titoliFilm[] = $row[0];
		$codiciFilm[] = $row[1];
	}

	$query = "Select nome,codiceSala from Sale";
	$result=mysql_query($query);
	$nomiSale=array();
	$codiciSale=array();
	while ($row = mysql_fetch_row($result)){
		$nomiSale[] = $row[0];
		$codiciSale[] =$row[1];
	}


	drawStartForm("/admin_spett.php","form-horizontal");

	echo '<div class="form-group">';
	echo '<label for="codiceFilm" class="col-sm-2 control-label">Film</label>';
	echo '<div class="col-sm-10">';
	echo '<select name = "codiceFilm" class="form-control">';
	echo "<option value=\"-1\">---</option>";
	for ($i=0; $i < count($codiciFilm) ; $i++) { 
		$f = $titoliFilm[$i];
		$c = $codiciFilm[$i];
		echo "<option value=\"$c\">$f</option>";
	}
	echo '</select>';
	echo '</div>';
	echo '</div>';


	echo '<div class="form-group">';
	echo '<label for="codiceSala" class="col-sm-2 control-label">Sala</label>';
	echo '<div class="col-sm-10">';
	echo '<select name = "codiceSala" class="form-control">';
	echo "<option value=\"-1\">---</option>";
	for ($i=0; $i < count($codiciSale) ; $i++) { 
		$f = $nomiSale[$i];
		$c = $codiciSale[$i];
		echo "<option value=\"$c\">$f</option>";
	}
	echo '</select>';
	echo '</div>';
	echo '</div>';

	drawFormField("number","costoPerPosto","Costo per posto",$_POST["costoPerPosto"],"","step=\"any\" min=\"0\"");

	drawFormField("date","data","Data",$_POST["data"],"","placeholder=\"aaaa-mm-gg\""); //Il placeholder è necessario perchè se il browser non supporta HTML5
	drawFormField("time","ora","Ora",$_POST["ora"],"","placeholder=\"hh:mm\"");			//viene visualizzata una normale casella di testo.

	echo '<div class="form-group">';
	echo '<div class="col-sm-offset-2 col-sm-10"><input type="submit" class="btn btn-default" value="Inserisci"/></div>';
	echo '</div>';
	drawHiddenField("action","insert");

	drawEndForm();


	echo '<hr></div></div>';

	echo '<div class="row"><div class ="col-md-12">';
	echo '<h3>Lista proiezioni</h3>';


	drawStartTable(array("Titolo","Sala","Data","Ora","Costo per posto","Azioni"));
	$query = "select titolo, nome,DATE_FORMAT(data,'%e/%c/%Y'), TIME_FORMAT(ora,'%k:%i'), costoPerPosto, codiceProiezione 
			  from Proiezioni join Film on (film = codiceFilm) join Sale on (sala = codiceSala)
			  where data >= current_date() order by data, ora";

	$result = mysql_query($query);
	while ($row = mysql_fetch_row($result)){
		$js="return confirm('Cancellando una proiezione verranno anche cancellate tutte le prenotazioni che la riguardano. Sei sicuro di voler proseguire?');";
		$formPerCancellazione ='<form method="POST" action = "'.baseUrl().'admin_spett.php">
								<input type="submit" valure="Cancella" onClick="'.$js.'" value="Cancella" class="btn btn-danger btn-xs">
								<input type="hidden" name ="action" value="delete"/>
								<input type="hidden" name ="codiceProiezione" value="'.$row[5].'"/>
								</form>';
		drawTableRow(array($row[0],$row[1],$row[2],$row[3],$row[4],$formPerCancellazione));
	}
	drawEndTable();


	echo '<hr></div></div>';


}
endPage();

?>
<?php
require_once('./support/_components.php');
require_once('./support/_database.php');
require_once('./support/_various.php');
$autorizzato = startPage("Prenota",1);

if ($autorizzato){
	connect($dbcon);

	$DAY_INTERVAL = 15;
	$query = 	"Select codiceFilm,titolo,nome,DATE_FORMAT(data,'%e/%c/%Y'), TIME_FORMAT(ora,'%k:%i'),codiceProiezione, codiceSala,costoPerPosto 
				from Film join Proiezioni on (codiceFilm=film) join Sale on (codiceSala=sala)
				where data>=current_date() and data <= current_date() + interval $DAY_INTERVAL day";

	$result=mysql_query($query);

	while ($row = mysql_fetch_row($result)){
		$film["codiceFilm"] =$row[0];
		$film["titolo"] =$row[1];

		if (!isset($films[$film["codiceFilm"]]))
			$films[$film["codiceFilm"]]=$film;


		$proiezione["sala"]=$row[2];
		$proiezione["data"]=$row[3];
		$proiezione["ora"]=$row[4];
		$proiezione["codiceProiezione"]=$row[5];
		$proiezione["codiceSala"]=$row[6];
		$proiezione["costoPerPosto"]=$row[7];


		$films[$film["codiceFilm"]]["proiezioni"][$proiezione["codiceProiezione"]]=$proiezione;

	}
	
	if ($_POST["postiScelti"]){
		$postiPrenotatiStr=trim($_POST["postiPrenotati"]);
		$postiPrenotatiTmp = explode(" ",$postiPrenotatiStr);//è un array di stringhe del tipo A-12, A-21, B-2

		$codicePostiStr =trim($_POST["codicePostiPrenotati"]);
		$codicePosti = explode(" ",$codicePostiStr);

		for ($i=0; $i < count($postiPrenotatiTmp); $i++) { 
			$postiPrenotatiTmp[$i]=$postiPrenotatiTmp[$i]."-".$codicePosti[$i];
		}
		
		sort($postiPrenotatiTmp); //in questo modo ordino i posti 

		foreach ($postiPrenotatiTmp as $value) {
			$postoCorrente =explode("-",$value);
			$postiPrenotati[]=$postoCorrente;

			$ultimaFila=$postoCorrente[0];
			$ultimoNumero = $postoCorrente[1];
			$checkFile[$ultimaFila] = $ultimaFila;
			$checkPosti[] = $ultimoNumero;
		}

		$err = false;
		if (count($checkFile)>1){
			$_SESSION["ERROR_MSG"][]="I posti deveono essere nella stessa fila";
			$err=true;
		}
		//postiPrenotati[][0] è la fila, [][1] è il numero, [][2] è il codice.
		$cntPosti = end($checkPosti) - $checkPosti[0] +1;
		if ($cntPosti != count($checkPosti)){
			$err = true;
			$_SESSION["ERROR_MSG"][]="I posti devono essere vicini tra loro";
		}
		if (count($postiPrenotati)<=0){
			$err = true;
			$_SESSION["ERROR_MSG"][]="Devi selezionare almeno un posto";
		}

		if (!$err){
			mysql_query("set autocommit = 0");
			mysql_query("start transaction");
			$qp = "insert into Prenotazioni values(0,'".date("Y-m-d H:i:s")."',0,'".$_SESSION["username"]."',".$_POST["codiceProiezione"].")";
			
			$queryCompleta = $qp." ";
			$qp = mysql_query($qp);
			
			$queryLastID = "select LAST_INSERT_ID()";
			$row = mysql_fetch_row(mysql_query($queryLastID));
			$lastID=$row[0];
			$keepGoing =true;
			foreach ($postiPrenotati as $posto) {
				$insertPosti = " Insert into PostiPrenotati values($lastID,".$posto[2].");";
				$queryCompleta=$queryCompleta ." ".$insertPosti;
				$keepGoing = $keepGoing && mysql_query($insertPosti);
			}
			if ($keepGoing){
				mysql_query("COMMIT");
				mysql_query("set autocommit=1");
				$_SESSION["SUCCESS_MSG"][] = "Prenotazione inserita con successo";
				sendRecapMail($lastID);
			}else{
				mysql_query("ROLLBACK");
				$_SESSION["ERROR_MSG"][]="Qualcuno ti ha anticipato e mentre decidevi ha prenotato uno dei tuoi posti.";
			}
		}

	}//Fine if posti scelti



	drawLogo();
	drawUserBar(1);

	echo '<div class="row"><div class ="col-md-12">';
	echo '<h3>Prenota</h3>';
	drawStartForm("/prenota.php","form-horizontal");


	echo '<div class="form-group">';
	echo '<label for="codiceFilm" class="col-sm-2 control-label">Film</label>';
	echo '<div class="col-sm-10">';
	echo '<select name = "codiceFilm" class="form-control" onchange="submit()">';
	if ($_POST["filmScelto"]){
		echo "<option value=\"".$_POST["codiceFilm"]."\">".$films[$_POST["codiceFilm"]]["titolo"]."</option>";
	}
	echo "<option value=\"-1\">---</option>";
	foreach ($films as $key => $value) {
		echo "<option value=\"$key\">".$value["titolo"]."</option>";
	}
	echo '</select>';
	echo '</div>';
	echo '</div>';

	drawHiddenField("isPostBack","true");
	drawHiddenField("filmScelto","true");
	drawEndForm();


	// parte schela spettacolo
	drawStartForm("/prenota.php","form-horizontal");

	echo '<div class="form-group">';
	echo '<label for="codiceProiezione" class="col-sm-2 control-label">Proiezione</label>';
	echo '<div class="col-sm-10">';
	echo '<select name ="codiceProiezione" class="form-control" onchange="submit()">';

	if ($_POST["spettacoloScelto"]){
		$proiezione = $films[$_POST["codiceFilm"]]["proiezioni"][$_POST["codiceProiezione"]];
		echo "<option value=\"".$proiezione["codiceProiezione"]."\">".$proiezione["data"]." ".$proiezione["ora"]." ".$proiezione["sala"]."</option>";
	}

	echo "<option value=\"-1\">---</option>";
	if ($_POST["filmScelto"]){ //potrebbe essere necessario check !=-1
		$codiceFilm = $_POST["codiceFilm"];
		$proiezioni = $films[$codiceFilm]["proiezioni"];
		
		foreach ($proiezioni as $proiezione) {
			echo "<option value=\"".$proiezione["codiceProiezione"]."\">".$proiezione["data"]." ".$proiezione["ora"]." ".$proiezione["sala"]."</option>";
		}

	}

	echo '</select>';
	echo '</div>';
	echo '</div>';


	drawHiddenField("codiceFilm",$_POST["codiceFilm"]);
	drawHiddenField("filmScelto","true");
	drawHiddenField("spettacoloScelto","true");

	drawEndForm();

	echo '</div></div>';#fine riga


	echo '<div class="row">';#inizio riga 2
	echo '<div class ="col-md-9">';#colonna sala
	echo '<h4>Sala</h4>';

	if ($_POST["spettacoloScelto"]){
		$codiceProiezione=$_POST["codiceProiezione"];
		$costoPerPosto = $films[$_POST["codiceFilm"]]["proiezioni"][$codiceProiezione]["costoPerPosto"];
		$codiceSala = $films[$_POST["codiceFilm"]]["proiezioni"][$codiceProiezione]["codiceSala"];
		//$query = "select p.*,codicePrenotazione from Posti p natural left join (PostiPrenotati natural join Prenotazioni) where sala=$codiceSala and (proiezione=$codiceProiezione or  proiezione is null) order by fila,numero"; #il test su sale è necessario per trovare i posti non prenotati
		
		$query = "	select p.*, pp.codicePrenotazione
					from Posti p 
						natural left join (PostiPrenotati pp join Prenotazioni ppp 
							on (pp.codicePrenotazione = ppp.codicePrenotazione and ppp.proiezione = $codiceProiezione))
					where sala = $codiceSala
					order by fila, numero";


		$result = mysql_query($query);

		echo '<div class="container-sala">';
		echo '<div class="schermo"><h4>SCHERMO</h4></div>';
		echo '<table class="tabella-posti"><tbody>';
		$vecchiaFila="A";
		echo '<tr>';
		while ($row=mysql_fetch_row($result)){
			$codicePosto = $row[0];
			$fila = $row[1];
			$numero =$row[2];
			$prenotato = ($row[4]>0);
			if ($fila != $vecchiaFila){
				echo '</tr>';
				$vecchiaFila=$fila;
				echo '<tr>';
			}
			$tipoSfondo = ($prenotato)?"posto-occupato":"posto-libero";
			$tipoSedia = ($prenotato)?"occupata":"libera";
			if ($numero <=9 && $numero >= 1){ //prima di insieri i posti li ordino come stringhe per id cresente, facendo l'ordine lessicografico A-10 viene prima di A-9 questa parte di codice risolve l'inconvenientr
				$numero = "0".$numero;
			}
			echo "	<td><div class=\"posto-outer\">
						<div class=\"sfondo-sedia $tipoSfondo\"></div>
						<div class=\"sedia $tipoSedia\" id=\"$fila-$numero|$codicePosto\"></div>
					</div></td>";
		}
		echo '</tr>';
		echo '</tbody></table>';

		echo '</div>';#fine container sala

	}

	echo '</div>'; #fine colonna sala

	echo '<div class ="col-md-3">';#colonna sommario prenotazione
	echo '<h4>Posti scelti</h4>';


	drawStartForm("/prenota.php","form-horizontal");

	drawFormField("text","postiPrenotati","Posti","","","readonly");

	drawHiddenField("costoPerPosto",$costoPerPosto);
	drawHiddenField("codicePostiPrenotati","");

	drawFormField("text","costoPrenotazione","Totale","0","","readonly");
	drawFormField("submit","","","Prenota","btn btn-primary");


	drawHiddenField("codiceFilm",$_POST["codiceFilm"]);
	drawHiddenField("codiceProiezione",$_POST["codiceProiezione"]);
	drawHiddenField("filmScelto","true");
	drawHiddenField("spettacoloScelto","true");
	drawHiddenField("postiScelti","true");


	drawEndForm();
	echo '</div>'; #fine colonna sommario prenotazione
	echo '</div>'; #fine riga 2



	echo '<script src="//code.jquery.com/jquery-1.11.0.min.js"></script>';
	echo '<script src="'.baseUrl().'/js/postiApp.js"></script>';
}
endPage();
?>

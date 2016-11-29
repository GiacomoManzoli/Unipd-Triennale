$(document).ready(function(){
	var cntPosti=0;
	var costoPerPosto = $('#costoPerPosto').val();

	$(".sedia").on("click",function(){
		var parent = $(this).parent();
		var sfondoSedia = $(parent).children(".sfondo-sedia");

		if (! $(sfondoSedia).hasClass("posto-occupato")){
			if ($(this).hasClass("libera")){ //Devo occupare il posto
				

				// devo aggiungere alla lista dei posti il posto
				var id = $(this).attr("id").split("|");
				var oldVal = $("#postiPrenotati").val();

				var newVal = oldVal.concat(id[0]," ");
				$("#postiPrenotati").val(newVal);

				var oldCod = $("#codicePostiPrenotati").val();
				var newCod = oldCod.concat(id[1], " ");
				$("#codicePostiPrenotati").val(newCod);
				$(this).removeClass("libera");
				$(this).addClass("occupata")

				$(sfondoSedia).removeClass("posto-libero");
				$(sfondoSedia).addClass("posto-scelto");
				cntPosti++;
			}else{
				$(this).removeClass("occupata");
				$(this).addClass("libera")

				$(sfondoSedia).removeClass("posto-scelto");
				$(sfondoSedia).addClass("posto-libero");

				var oldVal = $("#postiPrenotati").val();
				var id = $(this).attr("id").split("|");
				id[0] = id[0].concat(" ");
				$("#postiPrenotati").val(oldVal.replace(id[0],""));

				var oldCod = $("#codicePostiPrenotati").val();
				id[1] = id[1].concat(" ");
				$("#codicePostiPrenotati").val(oldCod.replace(id[1],""));
				cntPosti--;
			}
			var costo = cntPosti*costoPerPosto;
			var costoStr = "".concat(costo," Euro");
			$('#costoPrenotazione').val(costoStr);
		}
	});
});
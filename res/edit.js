/**
 * @name popup edit data from table
 * @type JS,jQuery
 * @requires jQuery v1.8.0
 * @author prodilshod(prodilshod@gmail.com)
 * @version 1.0.0
 * @DATE 2013-06-28
*/
$(function(){
	//global virables
	var _id = 0;
	var _data = "";
	var _donejob = 0;
	
	//   all functions
	
	var send_save_data = function(){
		console.log(_id);
		console.log(_data);
		console.log(_donejob);
		eval("var appdata ={"+_data+",donejob:"+_donejob+"};");
		
		$.ajax({
			type: "POST",
			url: "lib/ajax/sicamp_save_data.php",
			data:{'data':appdata},
			complete:function(data){
				_status_data = data.responseText;
				if(_status_data=="success"){
					$("#"+_id).html(_donejob+"%");
				}else{
					alert(_status_data);
				}
			}
		});
	}
	var save_popup = function(){
		_donejob = parseFloat($("#modal_data").val());
		if(_donejob>=0 && _donejob<=100){
			send_save_data();
			$("#modal_data").css({'background':'#FFF'});
			$("#modal_data").val("");
			$("#myModal").modal('hide');
		}else{
			$("#modal_data").css({'background':'#F00'});
		}
	}
	
	
	//       All Binds
	
	$("button.popups").bind("click",function(){
		_id=$(this).attr("id");
		_data=$(this).attr("data");
		$("#myModal").modal('show');
	});

	$("#myModal").modal({
		backdrop:true,
		show:false,
	});

	$("#myModal").on("shown", function(){
		$("#modal_data").focus();
	});
	
	$("#modal_close").bind("click",function(){
		$("#myModal").modal('hide');
	});

	$("#modal_save").bind("click",function(){
		save_popup();
	});
	$("#modal_data").bind("keyup",function(e){
		if(e.keyCode==13){
			save_popup();
		}
	});
})
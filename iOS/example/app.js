// this sets the background color of the master UIView (when there are no windows/tab groups on it)
Titanium.UI.setBackgroundColor('#000');

// create tab group
var tabGroup = Ti.UI.createTabGroup();

var onetok = require('ti.onetok');
Ti.API.info("module is => " + onetok);
var oneTokSession = onetok.createSession();
oneTokSession.showInConsole(true);

var appConfigs = [
	{
		title: "Bank",
		hostName : "http://sandbox.onetok.com:8080",
		appID : "ATV6I5WSLHE47GLXV9MX",
		appToken : "1729DF0B-FFC2-4DA3-8C67-DF8D1E9357E5",
		version : "0.1"
	},
	{
		title : "Bg colors",
		hostName : "http://sandbox.onetok.com:8080",
		appID : "IQTLDGOJS1AKBBFWNXHA",
		appToken : "805BC740-243F-4E63-B3F5-BF4FCD6299BA",
		version : "0.1"
	},
	{
		title : "Weather",
		hostName : "http://sandbox.onetok.com:8080",
		appID : "YOICDYSXMORP8QQISCZ5",
		appToken : "70A299D4-B210-4C88-800B-73F113D830B8",
		version : "0.1"
	}
];

var configIndex=0;

function fetchWindowTwo(){
	var isRecording = false;
	
	var win = Ti.UI.createWindow({
		backgroundColor:'#fff',
		title:'Test Recording',
		tabBarHidden:true
	});
	
	var btnRecord = Ti.UI.createButton({
		title:'Start Recording', height:40, width:150, left:7, top:20
	});
	win.add(btnRecord);
	
	var tableView = Ti.UI.createTableView({
		top:70,bottom:0, width:Ti.UI.FILL
	});
	win.add(tableView);
	
	function turnOff(){
		isRecording=false;
		btnRecord.title= ((isRecording) ? 'Stop Recording' : 'Start Recording');
	};
	
	function manageRecordState(){
		isRecording=!(isRecording);
		btnRecord.title= ((isRecording) ? 'Stop Recording' : 'Start Recording');
		
		if(isRecording){
			tableView.setData([]);
			startRecording();
		}else{
			oneTokSession.stopRecording();	
		}					
	};
	
	btnRecord.addEventListener('click', function(){
		manageRecordState();
	});		
	
	function addRow(sessionId,outputResult,resultType,analysisStatus){
		
		var row = Ti.UI.createTableViewRow({	
			selectedBackgroundColor:'#c7c8ca', backgroundColor:'#fff', height:220, hasChild:false		
		});
	
		var vwRow = Ti.UI.createView({
			left:0,right:0,height:220, layout:'vertical'
		});
		
		var label1 = Ti.UI.createLabel({
			text:'Session Id:', color:'#000', textAlign:'left', top:7, right:7, left:7, height:18,
			font:{fontSize:14}
		});
		vwRow.add(label1);

		var label2 = Ti.UI.createLabel({
			text:sessionId, color:'#000', textAlign:'left', top:7, right:7, left:7, height:20,
			font:{fontSize:14,fontWeight:'bold'}
		});
		vwRow.add(label2);
		
		var label3 = Ti.UI.createLabel({
			text:'Results:', color:'#000', textAlign:'left', top:7, right:7, left:7, height:18,
			font:{fontSize:14}
		});
		vwRow.add(label3);

		var label4 = Ti.UI.createLabel({
			text:outputResult, color:'#000', textAlign:'left', top:7, right:7, left:7, height:20,
			font:{fontSize:14,fontWeight:'bold'}
		});
		vwRow.add(label4);
		
		var label5 = Ti.UI.createLabel({
			text:'Result Type:', color:'#000', textAlign:'left', top:7, right:7, left:7, height:18,
			font:{fontSize:14}
		});
		vwRow.add(label5);

		var label6 = Ti.UI.createLabel({
			text:resultType, color:'#000', textAlign:'left', top:7, right:7, left:7, height:20,
			font:{fontSize:14,fontWeight:'bold'}
		});
		vwRow.add(label6);
		
		var label7 = Ti.UI.createLabel({
			text:'Analysis Status:', color:'#000', textAlign:'left', top:7, right:7, left:7, height:18,
			font:{fontSize:14}
		});
		vwRow.add(label7);

		var label8 = Ti.UI.createLabel({
			text:analysisStatus, color:'#000', textAlign:'left', top:7, right:7, left:7, height:20,
			font:{fontSize:14,fontWeight:'bold'}
		});
		vwRow.add(label8);
						
		row.add(vwRow);
		
		tableView.appendRow(row);
					
	};
	
	function startRecording(){

		//This method is called on error
		function onError(e){
			Ti.API.info(e);
			alert('Errored while recording');
			turnOff();
		};
		
		//This method is called as OneTok processes your
		//speak results. This will be called several times before finish
		function onResults(e){
			Ti.API.info("results=" + JSON.stringify(e));
			addRow(e.session_id,e.result,e.result_type,e.analysis_status);
		};
		
		//This method is called when the recording session has finished
		function onFinish(e){
			alert('Recording Completed');
			turnOff();
		};
		
		if(!Ti.Network.online){
			alert("I'm sorry a network connection is needed to use this module");
		}else{		
			oneTokSession.startRecording({
					onResults:onResults, //Add callback to process results, called many times 
					onError:onError, //Add callback to handle error messages
					onFinish:onFinish  //Add callback to handle when recording has finished
			});
		}	
	};

	return win;
};
function fetchWindowOne(){

	var win = Ti.UI.createWindow({
		backgroundColor:'#fff',
		title:'Select Connection',
		tabBarHidden:true
	});
	
	var infoLabel = Ti.UI.createLabel({
		text:'Select Your App Configuration',
		top:20, left:7, right:7, height:24, font:{fontSize:16,fontWeight:'bold'}
	});
	win.add(infoLabel);
	
	var picker = Ti.UI.createPicker({top:50, height:50});
	picker.add(appConfigs);
	win.add(picker);
	picker.selectionIndicator = true;
	
	picker.setSelectedRow(0,0,true);

	picker.addEventListener('change',function(e){
		configIndex = e.rowIndex;
	});
	
	var btnAuthenticate = Ti.UI.createButton({
		title:'Authenticate',
		height:40,
		width:200,
		bottom:60
	});
	
	win.add(btnAuthenticate);

	btnAuthenticate.addEventListener('click', function(){
		function onError(e){
			Ti.API.info(e);
			alert('Errored on Authentication');
		};
		function onSuccess(e){
			Ti.API.info('Authenticated Successfully, opening recording window');
			tab1.open(fetchWindowTwo());
		};
		if(!Ti.Network.online){
			alert("I'm sorry a network connection is needed to use this module");
		}else{
			oneTokSession.authenticate({
					hostName : appConfigs[configIndex].hostName,
					appID : appConfigs[configIndex].appID,
					appToken : appConfigs[configIndex].appToken,
					version : appConfigs[configIndex].version,
					onSuccess:onSuccess,
					onError:onError 		
			});		
		}		
	});
	
	return win;
};

var tab1 = Ti.UI.createTab({  window: fetchWindowOne() });
tabGroup.addTab(tab1);  

// open tab group
tabGroup.open();
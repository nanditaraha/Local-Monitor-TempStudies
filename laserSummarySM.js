$(function() {
	'use strict';
	var crateNum = parseInt($('crtnum').text());
	var timeout = 1000;
	var lmprefix = 'lm';
	var smprefix = 'sm';
	var maxChannel = 30;

	Array.prototype.avg = Array.prototype.avg || function () {
	    return this.reduce(function(p,c,i,a){return p+(c/a.length)},0);
	};

	Array.prototype.size = Array.prototype.size || function () {
	    return this.reduce(function(p,c,i,a){return a.length},0);
	};

	var channels = [];
	/* Old Map
	channels[0] = 25-25;//pmt_1
	channels[1] = 26-25;//pid1_1
	channels[2] = 27-25;//pid2_1
	*/

	channels[0] = 27;//pmt_1 
	channels[1] = 18;//pid1_1
        channels[2] = 19;//pid2_1 
	channels[3] = 20;//lm10_1
	channels[4] = 20;//lm11_1
	channels[5] = 23;//lm20_1
	channels[6] = 23;//lm21_1
	channels[7] = 21;//lm30_1
	channels[8] = 21;//lm31_1
	channels[9] = 22;//lm40_1
	channels[10] = 22;//lm41_1

	/*
	channels[11] = 30-25;//pmt_2
	channels[12] = 31-25;//pid1_2
	channels[13] = 32-25;//pid2_2
	*/
	channels[11] = 26;//pmt_2
	channels[12] = 15;//pid1_2
	channels[13] = 16;//pid2_2
	channels[14] = 11;//lm10_2
	channels[15] = 11;//lm11_2
	channels[16] = 17;//lm20_2
	channels[17] = 17;//lm21_2
	channels[18] = 12;//lm30_2
	channels[19] = 12;//lm31_2
	channels[20] = 14;//lm40_2
	channels[21] = 14;//lm41_2
	
	/*
	channels[22] = 35-25;//pmt_3
	channels[23] = 36-25;//pid1_3
	channels[24] = 37-25;//pid2_3
	*/
	channels[22] = 25;//pmt_3
	channels[23] = 12;//pid1_3
	channels[24] = 13;//pid2_3
	channels[25] = 15;//lm10_3
	channels[26] = 15;//lm11_3
	channels[27] = 18;//lm20_3
	channels[28] = 18;//lm21_3
	channels[29] = 5;//lm30_3
	channels[30] = 5;//lm31_3
	channels[31] = 0;//lm40_3
	channels[32] = 0;//lm41_3

	/*
	channels[33] = 40-25;//pmt_4
	channels[34] = 41-25;//pid1_4
	channels[35] = 43-25;//pid2_4
	*/
	channels[33] = 24;//pmt_4
	channels[34] = 10;//pid1_4
	channels[35] = 11;//pid2_4
	channels[36] = 6;//lm10_4
	channels[37] = 6;//lm11_4
	channels[38] = 7;//lm20_4
	channels[39] = 7;//lm21_4
	channels[40] = 9;//lm30_4
	channels[41] = 9;//lm31_4
	channels[42] = 1;//lm40_4
	channels[43] = 1;//lm41_4

	/*
	channels[44] = 49-25;//pmt_5
	channels[45] = 46-25;//pid1_5
	channels[46] = 48-25;//pid2_5
	*/
	channels[44] = 23;//pmt_5
	channels[45] = 7;//pid1_5
	channels[46] = 8;//pid2_5
	channels[47] = 2;//lm10_5
	channels[48] = 2;//lm11_5
	channels[49] = 8;//lm20_5
	channels[50] = 8;//lm21_5
	channels[51] = 3;//lm30_5
	channels[52] = 3;//lm31_5
	channels[53] = 4;//lm40_5
	channels[54] = 4;//lm41_5

	/*
	channels[55] = 50-25;//pmt_6
	channels[56] = 51-25;//pid1_6
	channels[57] = 52-25;//pid2_6
	*/
	channels[55] = 21;//pmt_6
	channels[56] = 5;//pid1_6
	channels[57] = 6;//pid2_6
	channels[58] = 16;//lm10_6
	channels[59] = 16;//lm11_6
	channels[60] = 13;//lm20_6
	channels[61] = 13;//lm21_6
	channels[62] = 19;//lm30_6
	channels[63] = 19;//lm31_6
	channels[64] = 10;//lm40_6
	channels[65] = 10;//lm41_6
    
	var laserNum = [];
	for(var i = 0; i < 6; i++) 
	  laserNum[i]=i+1;
	
	var pmt = [];//0;
	for(var i = 0; i < 6; i++)
	    pmt[i]=0;

	var pid1 = [];//1;
	for(var i = 0; i < 6; i++)
	    pid1[i] = 1;

	var pid2 = [];//2;
	for(var i = 0; i < 6; i++)
	    pid2[i] = 2;

	var lm10 = [];//3;
	for(var i = 0; i < 6; i++)
	    lm10[i] = 3;

	var lm11 = [];//3;
	for(var i = 0; i < 6; i++)
	    lm11[i] = 3;

	var lm20 = [];//4;
	for(var i = 0; i < 6; i++)
	    lm20[i] = 4;

	var lm21 = [];//4;
	for(var i = 0; i < 6; i++)
	    lm21[i] = 4;

	var lm30 = [];//5;
	for(var i = 0; i < 6; i++)
	    lm30[i] = 5;

	var lm31 = [];//5;
	for(var i = 0; i < 6; i++)
	    lm31[i] = 5;

	var lm40 = [];//6;
	for(var i = 0; i < 6; i++)
	    lm40[i] = 6;

	var lm41 = [];//6;
	for(var i = 0; i < 6; i++)
	    lm41[i] = 6;
	
	for(var j = 0; j < 6; j++){
	    for(var i = 0; i < 6; i++){
		if (laserNum[j] == i + 1){
		    pmt[j] = channels[10*i + laserNum[j] - 1];
		    pid1[j] = channels[10*i + laserNum[j]];
		    pid2[j] = channels[10*i + 1 + laserNum[j]];
		    lm10[j] = channels[10*i + 2 + laserNum[j]];
		    lm11[j] = channels[10*i + 3 + laserNum[j]];
		    lm20[j] = channels[10*i + 4 + laserNum[j]];
		    lm21[j] = channels[10*i + 5 + laserNum[j]];
		    lm30[j] = channels[10*i + 6 + laserNum[j]];
		    lm31[j] = channels[10*i + 7 + laserNum[j]];
		    lm40[j] = channels[10*i + 8 + laserNum[j]];
		    lm41[j] = channels[10*i + 9 + laserNum[j]];
		}
	    }
	}

	function setAlarms(data) {
            var lmamps = data.runningAvgHists[lmprefix + 'AMPS'+crateNum.toString() + "_0"];
            var smamps = data.runningAvgHists[smprefix + 'AMPS'+crateNum.toString() + "_0"];
            var lmamps2 = data.runningAvgHists[lmprefix + 'AMPS'+crateNum.toString() + "_0_2"];
            $eventNum.text(smamps.eventNum);
            $runNum.text(smamps.runNum);
	    if (typeof lmamps !== 'undefined' && typeof smamps !== 'undefined' && typeof lmamps2 !== 'undefined'){
                for(var i = 0; i < 6; i++){
                    var a = 'btn1';
                    if(i==1)a='btn2';if(i==2)a='btn3';if(i==3)a='btn4';if(i==4)a='btn5';if(i==5)a='btn6';
                    if( smamps.last[channels[11*i]] > 100 &&//pmt 
			smamps.last[channels[11*i + 1]] > 100 &&//pid1
			smamps.last[channels[11*i + 2]] > 100 &&//pid2
			lmamps.last[channels[11*i + 3]] > 100 &&//lm10 
			lmamps2.last[channels[11*i + 4]] > 1//lm11
			){
			document.getElementById(a).style.background='green';
		    }
		    else{
                        document.getElementById(a).style.background='red';
                    }
                }
            }
	}
	
	function setPage(j) {//j is laser number
	    l1History[j]=document.getElementById('l'+(j+1).toString()+'History');
	    lm1History[j]=document.getElementById('lm'+(j+1).toString()+'History');
	    //Three plots overlaid - PD1, PD2 and PD2:PD1
	    Plotly.newPlot('l'+(j+1).toString()+'History', [
							    { y: [],  type: 'trace', mode: 'lines' },{ y: [],  type: 'trace', mode: 'lines' },{ y: [],  type: 'trace', mode: 'lines' }], {

	    
			       //xaxis: { title: 'Event num', 'titlefont': { size: 15 }}, autobinx:'true',// autorange: 'true'}, //, range: [0, 15000] },
			       xaxis: { title: 'Event num', 'titlefont': { size: 15 }}, range: [0, 100],
											    yaxis: { title: 'Amplitude', titlefont: { size: 15 }, autorange: 'true' }
				   //legend: { orientation: 'h', font: { size: 10 } }
			   });

	     Plotly.newPlot('lm'+(j+1).toString()+'History', [
							      { y: [],  type: 'histogram' }], {
				title: 'Laser '+(j+1).toString()+' normalized sync amplitude history', titlefont: { size: 15 },
                                                                                        
				    xaxis: { title: 'Event num', 'titlefont': { size: 15 }},
				    //range: [11000, 12500],autorange: 'false', autobinx:'true',//, range: [0, 15000] },
				    yaxis: { title: 'Amplitude of PMT', titlefont: { size: 15 }, autorange: 'true' }
			    });
	     

	    //Plotly.newPlot('lm'+(j+1).toString()+'History', data);
	    socket.on('requested objects', function(data) {
		    setAlarms(data);
		    //SM pulses 
		    pmtHistory[j] = data.histories[smprefix + 'AMP' + crateNum.toString() + pmt[j] + "_0"];
		    pid1History[j] = data.histories[smprefix + 'AMP' + crateNum.toString()+ pid1[j] + "_0"];
		    pid2History[j] = data.histories[smprefix + 'AMP' + crateNum.toString()+ pid2[j] + "_0"];
		    		   
		    //these must be 2-d vectors/arrays to save event# and laser#
		    var pmt_norm=[];
		    var pid1_norm=[];
		    var pid2_norm=[];
		    var bin_size = 1;
		   
		    for(var i=0;i<pid1History[j].y.length;i++){
		       ratio[j]=new Array(pid1History[j].y.length);
		       pmt_norm[j]=new Array(pid1History[j].y.length);
		       pid1_norm[j]=new Array(pid1History[j].y.length);
		       pid2_norm[j]=new Array(pid1History[j].y.length);

		    }

		    setTimeout(function() {
			    var smamps = data.runningAvgHists[smprefix + 'AMPS'+crateNum.toString() + "_0"];
			    if ( typeof pid1History[j] !== 'undefined') {
				ratio[j][i]=0;
				pid1_norm[j][i]=0;
				pid2_norm[j][i]=0;			
				for(var i=0;i<pid1History[j].y.length;i++){
				    if(pid1History[j].y[i]>100 && pid2History[j].y[i]>100){
					ratio[j][i]=(pid2History[j].y[i]/pid1History[j].y[i])/(pid2History[j].y[i]/pid1History[j].y[0]);
					
					//pid2_norm[j][i]=pid2History[j].y[i]/pid2History[j].y[0];
				    }
				    else if(pid1History[j].y[i]<101 && pid2History[j].y[i]<101) ratio[j][i]= 0;
				    //ratio[j][i]=(pid2History[j].y[i]/pid1History[j].y[i])/(pid2History[j].y[i]/pid1History[j].y[0]);
				    if(pid1History[j].y[i]>100)
					pid1_norm[j][i]=pid1History[j].y[i]/pid1History[j].y[0];
				    else if(pid1History[j].y[i]<101)
					pid1_norm[j][i]=0;
				    if(pid2History[j].y[i]>100)
					pid2_norm[j][i]=pid2History[j].y[i]/pid2History[j].y[0];
                                    else if(pid2History[j].y[i]<101)
					pid2_norm[j][i]=0;
				    
				    if(pmtHistory[j].y[i]>100)
					pmt_norm[j][i]=pmtHistory[j].y[i]/pmtHistory[j].y[0];
				    else if(pmtHistory[j].y[i]<101)
					pmt_norm[j][i]=0;
					
				}
				
				Plotly.deleteTraces(l1History[j], [0,1,2]);
				
				//ref for colors
				//var channelNames = ['PMT','PID1','PID2','LM1-0','LM1-1','LM2-0','LM2-1','LM3-0','LM3-1','LM4-0','LM4-1']; 
				//var colors = ['green','blue','red','dimgray','black','purple','aqua','chartreuse','brown','darkgreen','gold'];
				
				    Plotly.addTraces(l1History[j], [{x: pmtHistory[j].x, y: ratio[j], name:'PiD2:PiD1',mode: 'lines' , marker: { color: 'black'}}, 
								{x: pid1History[j].x, y: pid1_norm[j], name:'PiD1',mode: 'lines' , marker: { color: 'blue'}},
								{x: pid2History[j].x, y: pid2_norm[j], name:'PiD2',mode: 'lines' , marker: { color: 'red'}}]);
				    /*
				if(pid1History[j].y[i]<100 && pid2History[j].y[i]<100)
				    Plotly.addTraces(l1History[j], [{x: pmtHistory[j].x, y: 0, name:'PiD2:PiD1',mode: 'lines' , marker: { color: 'black'}},
								   {x: pid1History[j].x, y: 0, name:'PiD1',mode: 'lines' , marker: { color: 'blue'}},
								   {x: pid2History[j].x, y: 0, name:'PiD2',mode: 'lines' , marker: { color: 'red'}}]);
				    */				   
				Plotly.deleteTraces(lm1History[j], 0);
				
				//
				Plotly.addTraces(lm1History[j], {x: pmtHistory[j].x, y: pmt_norm[j], name:'PMT',mode: 'lines' , marker: { color: 'green'}});
				//Plotly.addTraces(lm1History[j], {x: pmtHistory[j].x, y: pmtHistory[j].y, name:'PMT',mode: 'lines' , marker: { color: 'green'}});
				    /*if(pmtHistory[j].y[i]<100)
				    Plotly.addTraces(lm1History[j], {x: pmtHistory[j].x, y: 0, name:'PMT',mode: 'lines' , marker: { color: 'green'}});
				    */							    
    
			    }
			}, 0);
		});
	}

	var socket = io('/', { path: '/lasersocket' + crateNum });
	registerCommonCallbacks(socket);

	var pmtHistory = [];
	var pid1History = [];
	var pid2History = [];
	var lm11History = [];//Data for lm laser1 amp1
        var lm12History = [];//Data for lm laser1 amp2
	var lm21History = [];//Data for lm laser2 amp1
	var lm22History = [];//Data for lm laser2 amp2
        var lm31History = [];//Data for lm laser3 amp1
        var lm32History = [];//Data for lm laser3 amp2
	var lm41History = [];//Data for lm laser4 amp1
        var lm42History = [];//Data for lm laser4 amp2

	var l1History = [];//Plotly names for SM
	var lm1History = [];//PLotly names for LM
	var ratio = [];
	//var ratio_norm = [];
	var ct=0;
	var pmt_avg=0;
	var pid1_avg=0;
	var pid2_avg=0;

	var $eventNum = $('#eventNum');                                                                                                    
	var $runNum = $('#runNum');

	for(var j=0; j<6; j++)
	    setPage(j);	

	// sochet calls for amps
	var historyStrings = [];
	historyStrings.push(lmprefix + 'nIslands' + crateNum.toString());
	historyStrings.push(smprefix + 'nIslands' + crateNum.toString());
	for (var i = 0; i < maxChannel; ++i) {
	    historyStrings.push(smprefix + 'AMP' + crateNum.toString() + i + "_0");
	    historyStrings.push(lmprefix + 'AMP' + crateNum.toString() + i + "_0");
	    historyStrings.push(lmprefix + 'AMP' + crateNum.toString() + i + "_0_2");
	}

	(function requestPlots() {
	    socket.emit('deliver objects', {
		    runningAvgHists: [lmprefix + 'AMPS'+crateNum.toString() + "_0",
				      lmprefix + 'AMPS'+crateNum.toString() + "_0_2",
				      smprefix + 'AMPS'+crateNum.toString() + "_0",
				      smprefix + 'AMPS'+crateNum.toString() + "_0_2"],
			histories: historyStrings
			});
	    setTimeout(requestPlots, timeout);
	})();

	socket.emit(lmprefix + 'nXtals?', crateNum);
	socket.emit(smprefix + 'nXtals?', crateNum);
	handleLaserModeUpdates();
    });

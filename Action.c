Action()
{
	int costSum = 7000;
	char* ArriveCityOFF;
	char* priceTicketChar;
	int countTicket;
	int priceTicket;
	int numberChoice;
	
	while (costSum > 0) {
	
	
	web_reg_save_param_ex(
		"ParamName=SeatingPref",
		"LB=seatPref\" value=\"",
		"RB=\"",
		"Ordinal={Random1}",
		SEARCH_FILTERS,
		LAST);
	
	web_reg_save_param_ex(
		"ParamName=TypeofSeat",
		"LB=seatType\" value=\"",
		"RB=\"",
		"Ordinal={Random2}",
		SEARCH_FILTERS,
		LAST);
	
	
	
	web_url("welcome.pl", 
		"URL=http://localhost:1080/cgi-bin/welcome.pl?page=search", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=home", 
		"Snapshot=t5.inf", 
		"Mode=HTML", 
		LAST);
		
		numberChoice = atoi(lr_eval_string("{RandomCost}"));
		lr_save_int(numberChoice, "Choice");
		lr_output_message("Podydok choosen ticket is: %s", lr_eval_string("{Choice}"));
		
	web_reg_save_param_ex(
		"ParamName=CostticketOut",
		"LB=\"outboundFlight\" value=\"",
		"RB=\"",
		"Ordinal={Choice}",
		SEARCH_FILTERS,
		LAST);
		
	web_reg_save_param_ex(
		"ParamName=PriceTicket",
		"LB=;",
		"RB=;{DepartDate}\"",
		"Ordinal={Choice}",
		SEARCH_FILTERS,
		LAST);
	
		ArriveCityOFF = lr_eval_string("{ArriveCity}");
		lr_save_string(ArriveCityOFF, "ArriveOFF");


	web_submit_data("reservations.pl", 
		"Action=http://localhost:1080/cgi-bin/reservations.pl", 
		"Method=POST", 
		"TargetFrame=", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/reservations.pl?page=welcome", 
		"Snapshot=t6.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=advanceDiscount", "Value=0", ENDITEM, 
		"Name=depart", "Value={HomeCity}", ENDITEM, 
		"Name=departDate", "Value={DepartDate}", ENDITEM, 
		"Name=arrive", "Value={ArriveOFF}", ENDITEM, 
		"Name=returnDate", "Value={ReturnDate}", ENDITEM, 
		"Name=numPassengers", "Value=1", ENDITEM, 
		"Name=seatPref", "Value={SeatingPref}", ENDITEM, 
		"Name=seatType", "Value={TypeofSeat}", ENDITEM, 
		"Name=.cgifields", "Value=roundtrip", ENDITEM, 
		"Name=.cgifields", "Value=seatType", ENDITEM, 
		"Name=.cgifields", "Value=seatPref", ENDITEM, 
		"Name=findFlights.x", "Value=67", ENDITEM, 
		"Name=findFlights.y", "Value=9", ENDITEM, 
		LAST);
	
		priceTicketChar = lr_eval_string("{PriceTicket}");
		priceTicket = atoi(priceTicketChar);
		costSum = costSum - priceTicket;
		lr_output_message("Price of current ticket is: %s",lr_eval_string("{PriceTicket}"));
		lr_save_int(costSum, "currentSumMoney");
		lr_output_message("Ostatok deneg na rykax: %s",lr_eval_string("{currentSumMoney}"));
		
		if (costSum < 0) {
			break;
		}
		


	web_submit_data("reservations.pl_2", 
		"Action=http://localhost:1080/cgi-bin/reservations.pl", 
		"Method=POST", 
		"TargetFrame=", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/reservations.pl", 
		"Snapshot=t7.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=outboundFlight", "Value={CostticketOut}", ENDITEM, 
		"Name=numPassengers", "Value=1", ENDITEM, 
		"Name=advanceDiscount", "Value=0", ENDITEM, 
		"Name=seatType", "Value={TypeofSeat}", ENDITEM, 
		"Name=seatPref", "Value={SeatingPref}", ENDITEM, 
		"Name=reserveFlights.x", "Value=32", ENDITEM, 
		"Name=reserveFlights.y", "Value=6", ENDITEM, 
		LAST);


	web_submit_data("reservations.pl_3", 
		"Action=http://localhost:1080/cgi-bin/reservations.pl", 
		"Method=POST", 
		"TargetFrame=", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/reservations.pl", 
		"Snapshot=t8.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=firstName", "Value={FirstName}", ENDITEM, 
		"Name=lastName", "Value={LastName}", ENDITEM, 
		"Name=address1", "Value={Address}", ENDITEM, 
		"Name=address2", "Value={State}", ENDITEM, 
		"Name=pass1", "Value={FullName}", ENDITEM, 
		"Name=creditCard", "Value={CardCredit}", ENDITEM, 
		"Name=expDate", "Value={ExpDate}", ENDITEM, 
		"Name=oldCCOption", "Value=", ENDITEM, 
		"Name=numPassengers", "Value=1", ENDITEM, 
		"Name=seatType", "Value={TypeofSeat}", ENDITEM, 
		"Name=seatPref", "Value={SeatingPref}", ENDITEM, 
		"Name=outboundFlight", "Value={CostticketOut}", ENDITEM, 
		"Name=advanceDiscount", "Value=0", ENDITEM, 
		"Name=returnFlight", "Value=", ENDITEM, 
		"Name=JSFormSubmit", "Value=off", ENDITEM, 
		"Name=.cgifields", "Value=saveCC", ENDITEM, 
		"Name=buyFlights.x", "Value=73", ENDITEM, 
		"Name=buyFlights.y", "Value=10", ENDITEM, 
		LAST);
	
		countTicket = countTicket +1;
		lr_save_int(countTicket, "countTicket");
		lr_output_message("Number of bought mine tickets: %s",lr_eval_string("{countTicket}"));
		lr_output_message("Departure City: %s",lr_eval_string("{HomeCity}"));
		lr_output_message("Arrive City: %s",lr_eval_string("{ArriveOFF}"));
		lr_output_message("Cost ticket OUT: %s",lr_eval_string("{CostticketOut}"));
		lr_output_message("Seating Preference: %s",lr_eval_string("{SeatingPref}"));
		lr_output_message("Type of Seat: %s",lr_eval_string("{TypeofSeat}"));
		lr_output_message("-------------------------------------------------------------");
		
	}
		

	return 0;
}
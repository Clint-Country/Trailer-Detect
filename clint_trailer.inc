
forward OnJugadorAttackTrailer(playerid,vehicleid,trailerid);
forward OnJugadorQuitarTrailer(playerid,vehicleid,trailerid);

new VehTrailer[MAX_PLAYERS] = {INVALID_VEHICLE_ID,...};
new LastVeh[MAX_PLAYERS] = {INVALID_VEHICLE_ID,...};

public OnPlayerUpdate(playerid)
{
	if(IsPlayerInAnyVehicle(playerid))
	{
	    if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
	    {
			new veh = GetPlayerVehicleID(playerid);
			if(veh == LastVeh[playerid])
			{
				new tr = GetVehicleTrailer(veh);
				if(tr != 0)
				{
				    if(VehTrailer[playerid] != INVALID_VEHICLE_ID)
				    {
				        if(VehTrailer[playerid] != tr)
				        {
					        if(funcidx("OnJugadorQuitarTrailer") != -1) CallLocalFunction("OnJugadorQuitarTrailer","ddd",playerid,veh,VehTrailer[playerid]);
		                    VehTrailer[playerid] = tr;
		                   	if(funcidx("OnJugadorAttackTrailer") != -1) CallLocalFunction("OnJugadorAttackTrailer","ddd",playerid,veh,tr);
						}
					}
					else
					{
	    				VehTrailer[playerid] = tr;
					    if(funcidx("OnJugadorAttackTrailer") != -1) CallLocalFunction("OnJugadorAttackTrailer","ddd",playerid,veh,tr);
					}
				}
				else
				{
				    if(VehTrailer[playerid] != INVALID_VEHICLE_ID)
				    {
				        if(funcidx("OnJugadorQuitarTrailer") != -1) CallLocalFunction("OnJugadorQuitarTrailer","ddd",playerid,veh,VehTrailer[playerid]);
				        VehTrailer[playerid] = INVALID_VEHICLE_ID;
					}
				}
			}
			else
			{
				LastVeh[playerid] = veh;
				new tr = GetVehicleTrailer(veh);
				if(tr != 0) VehTrailer[playerid] = tr;
				else VehTrailer[playerid] = INVALID_VEHICLE_ID;
			}
		}
	}
	if(funcidx("pig_OnPlayerUpdate") != -1) CallLocalFunction("pig_OnPlayerUpdate","d",playerid);
	return 1;
}

#if defined _ALS_OnPlayerUpdate
    #undef OnPlayerUpdate
#else
    #define _ALS_OnPlayerUpdate
#endif
#define OnPlayerUpdate pig_OnPlayerUpdate
forward pig_OnPlayerUpdate(playerid);

public OnPlayerStateChange(playerid, newstate, oldstate)
{
	if(newstate == PLAYER_STATE_DRIVER)
	{
		LastVeh[playerid] = GetPlayerVehicleID(playerid);
		new tr = GetVehicleTrailer(LastVeh[playerid]);
		if(tr != 0) VehTrailer[playerid] = tr;
	}
	if(oldstate == PLAYER_STATE_DRIVER)
	{
		LastVeh[playerid] = INVALID_VEHICLE_ID;
		VehTrailer[playerid] = INVALID_VEHICLE_ID;
	}
	if(funcidx("pig_OnPlayerStateChange") != -1) CallLocalFunction("pig_OnPlayerStateChange","ddd",playerid,newstate,oldstate);
    return 1;
}

#if defined _ALS_OnPlayerStateChange
    #undef OnPlayerStateChange
#else
    #define _ALS_OnPlayerStateChange
#endif
#define OnPlayerStateChange pig_OnPlayerStateChange
forward pig_OnPlayerStateChange(playerid, newstate, oldstate);

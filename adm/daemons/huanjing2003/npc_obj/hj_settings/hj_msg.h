// hj_msg.h
// ����Ϣ�����еص�

void hj_shout( string msg )
{
    int i;
    for(i=1;i<= HJ_ROOM_AMOUNT;i++)
    {
        if( find_object( HJ_DIR +"hj_room"+i ) )
            tell_room( HJ_DIR +"hj_room"+i,  msg );
    }
    tell_room( HJ_DIR + "room_door_hj", msg );
    tell_room( HJ_DIR + "room_gameover_hj", msg );
    tell_room( HJ_DIR + "room_master_hj", msg );
    tell_room( HJ_DIR + "room_readygo_hj", msg );
    tell_room( HJ_DIR + "room_cession_hj", msg );
}

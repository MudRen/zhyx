// ���ļ��� room_gameover_hj.c �� room_cession_hj.c ���á�
// 22:53 03-10-22


#define        MY_LOG_FILE_NAME        "huanjing/hj2003"

string get_log_file_name()
{
    int temp;

#ifdef        IS_TEST

temp = IS_TEST;

#endif

    if( temp )
        return MY_LOG_FILE_NAME + "_" + "testlog";

    return MY_LOG_FILE_NAME + ctime_format( "_YYM" );
}

// ÿ��������һ�� LOG��
// ���µ�LOG���̫��ʱ����MUDϵͳ�Զ���д�����ﲻ�����ǡ�
// ����ڲ���״̬���÷��Լ��һ���Ʒ�ļ�¼�����д����һ�� log �ļ��С�

// ��Ʒת�ô��� LOG �����ɡ�

void hj_log_file(string log_msg)
{
    if( !log_msg ) return;
    log_file( get_log_file_name(), log_msg );
}



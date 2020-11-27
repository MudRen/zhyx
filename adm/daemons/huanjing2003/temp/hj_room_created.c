// ������  /adm/daemons/ �£����ڻ��дȨ�������� hj �ķ����ļ���
// ʹ�� call_out() ��ʽ��������������
// naihe 13:27 03-10-19


#include <ansi.h>

string HJ_DIR;

void create()
{
    seteuid( getuid() );
}

string create_room( object me, string hj_dir, int last_num )
{
    if( !me || !wizardp(me) || getuid(me) != "naihe" )
        return "ֻ������ʦ �κ� ���ñ�����\n";

    if( !last_num || last_num < 30 || last_num > 200 || last_num % 10 != 0 )
        return "����������Χ 30 - 200 �����ұ�������ʮ����\n";

    HJ_DIR = hj_dir;

    remove_call_out( "create_room_now" );
    call_out( "create_room_now", 1, me, 1, last_num, 0 );
    message_vision( HIR"\n$N"HIR"������ �þ�һ ���������ļ�����\n\n"NOR, me);
    return "�����������佨�����򡭡�\n";
}

void create_room_now( object me, int now_num, int last_num, int create_amount )
{
    string filename, msg, content;

    if( !me || !wizardp(me) || getuid(me) != "naihe" )
        return;

    if( !last_num || last_num < 30 || last_num > 200 || last_num % 10 != 0 )
        return;

    filename = HJ_DIR + "hj_room" + now_num + ".c";

    msg = WHT"����д�룺 "+filename+ "  >>>>>>>>>>>>>  "NOR;



    if( file_size( filename ) == -1 )
    {
        // 1�ŷ���Ҫ�ر�д
        if( now_num == 1 )
            content = "

// ���þ�һ��ңԶ��˵֮��Ե���������֡� ��ͼ�����ļ�
// ��Ϊ�����һ�ŷ��䣬��ҪǶ��һ���ر���ļ���
// by "+base_name(this_object())+" , " +ctime_format() +"

#include <ansi.h>
inherit ROOM;

int mark=1;

#include \"1_room_info_special.h\"

";
        else content = "

// ���þ�һ��ңԶ��˵֮��Ե���������֡� ��ͼ�����ļ�
// by "+base_name(this_object())+" , " +ctime_format() +"

#include <ansi.h>
inherit ROOM;

int mark="+now_num+";

#include \"all_room_info_hj.h\"

";

// ��ʼд
        if( write_file( filename, content, 1 ) )
        {
            msg += HIG"�ɹ���\n"NOR;
            create_amount ++;
        }
        else msg += HIR"д��ʧ�ܡ�\n"NOR;
    }
    else msg += HIY"���и��ļ����ڡ�\n"NOR;

    message_vision( msg, me );

    now_num ++;
    if( now_num > last_num )
    {
        message_vision( HIR"\n�����ļ�������ϣ����ɹ����� "+create_amount+" ���ļ���\n\n"NOR, me);
        return;
    }

    remove_call_out( "create_room_now" );
    call_out( "create_room_now", 1, me, now_num, last_num, create_amount );
}



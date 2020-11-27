#include <ansi.h>
#include <errs_func.h>
#include <max_min.h>
inherit ROOM;


#define        LOG_WHERE        "/clone/allall/loglog.c"


void create()
{
    set("short", HIY"�þ�����ֲ�ѯ��"NOR);
    set("long", "


             ����  <check>  ָ���ð�����

\n");

    set("invalid_startroom",1);
    set("exits", ([
        "up": __DIR__"room_door_hj",
        ]));

    setup();
}

void init()
{
    add_action("do_ts", "check");
}

int shi, fen, miao;

int do_ts(string arg)
{
    string t, *tt, *plers;
    int i,j, t1,t2,t3,times,all, *temp;


    if( !arg ) return errs("���������

 high          -- ������� ���Եĳɹ�������߷�(���ڽ���1)

 xiaolv        -- ���Ч�ʵĵ÷�(�����뿴TOP �����)

 oktimes       -- ������� ���Ե��ܳɹ�����

 playtime      -- ������� ���Ե�����Ϸʱ��(���۳ɰ�)

 failtimes     -- ������� ���Ե���ʧ�ܴ���(100+�÷ֲ���)

 okscore       -- ������� ���Ե��ܳɹ��÷�\n");

    t = read_file ( LOG_WHERE );
    if( !t || !sizeof(t) ) return errs("�޷���ȡ�ļ� "+LOG_WHERE+" \n");

    t = replace_string( t, " ", "" );
    tt = explode( t, "\n" );

    plers = ({
      "addda",
      "anycall",
      "beeee",
      "chengfs",
      "fffjj",
      "jsxm",
      "kickyou",
      "lidaopao",
      "meir",
      "naihe",
      "net",
      "vsvic",
      "szcztzki",
      "xare",
      "xiaobc",
      "xiaxue",
      "xiuxiu",
      "xsmarter",
      "zll",
        });


if( arg == "high" )
{
// ÿ��ѡ���Լ���߷ֵ��Ǹ�
    write("ÿλ����Լ��ĵ��ֳɹ���߷֣�\n");

    for( j=0;j<sizeof(plers);j++ )
    {
        temp = ({ });
        for( i=0;i<sizeof(tt);i++ )
        {
            if( strsrch( tt[i], "��(Ч�ʣ�" ) != -1
             && strsrch( tt[i], plers[j] ) != -1 )
            {
                if( sscanf( tt[i], "%*s�÷�%d��(Ч�ʣ�%*s", t1 ) )
                    temp += ({ t1 });
            }
        }
        if( !temp || !sizeof(temp) )
        {
            write(sprintf("      %-8s          ---- ��\n",plers[j]) );
            continue;
        }
        write( sprintf("      %-8s          ---- %d\n", plers[j], max_min(temp, "max")));
    }

    return 1;
}

if( arg == "xiaolv" )
{
    temp = ({ });
    for( j=0;j<sizeof(plers);j++ )
    {
        for( i=0;i<sizeof(tt);i++ )
        {
            if( strsrch( tt[i], "��(Ч�ʣ�" ) != -1
             && strsrch( tt[i], plers[j] ) != -1 )
            {
                if( sscanf( tt[i], "%*s(Ч�ʣ�%d%*s", t1 ) )
                    temp += ({ t1 });
            }
        }
    }

    if( !temp || !sizeof(temp) )
        return errs("���κ��˳ɹ���û��Ч�ʼ�¼��\n");
    
    write("���Ч���ǣ�"+max_min( temp, "max" ) +" �㡣\n");
    return 1;
}

if( arg == "oktimes" )
{
    write("ÿλ��ҵĳɹ��ܴ�����\n");

    for( j=0;j<sizeof(plers);j++ )
    {
        times = 0;
        for( i=0;i<sizeof(tt);i++ )
        {
            if( strsrch( tt[i], "��(Ч�ʣ�" ) != -1
             && strsrch( tt[i], plers[j] ) != -1 )
                times ++;
        }
        t = sprintf( "      %-8s          ---- %2d ��\n",
            plers[j], times );
        if( !times ) t = replace_string( t, "0 ��", "  ��" );
        write( t );
    }
    return 1;
}

if( arg == "playtime" )
{
    write("ÿλ�������Ϸʱ��(���۳ɰ�)��\n");

    for( j=0;j<sizeof(plers);j++ )
    {
        shi=0;fen=0;miao=0;all=0;
        t1=0;t2=0;t3=0;

        for( i=0;i<sizeof(tt);i++ )
        {
            if( strsrch( tt[i], "��Ϸ" ) != -1 && strsrch( tt[i], plers[j] ) != -1 )
            {
                t1=0;t2=0;t3=0;
                if( sscanf( tt[i], "%*s��Ϸ%dʱ%d��%d��%*s", t1,t2,t3 ) )
                    shi += t1; fen += t2; miao += t3;
            }
        }

        all = shi * 3600 + fen * 60 + miao;
        write( sprintf( "      %-8s          ---- %2d:%2d:%2d\n",
            plers[j], all/3600, (all%3600)/60, all%3600%60 ) );
    }

    return 1;
}


if( arg == "failtimes" )
{
    write("ÿλ��ҵ���ʧ�ܴ�����100�ּ����ϵĻغϲż�����Чͳ�ƣ���\n");

    for( j=0;j<sizeof(plers);j++ )
    {
        times=0;
        t1 = 0;
        for( i=0;i<sizeof(tt);i++ )
        {
            if( strsrch( tt[i], plers[j] ) != -1
             && strsrch( tt[i], "ʧ�ܣ��÷�����") != -1 )
            {
                if( sscanf( tt[i], "%*s�÷�%d(ʧ�ܣ��÷�����)��", t1 ) )
                    if( t1 > 99 ) times++;
            }
        }
        t = sprintf( "      %-8s          ---- %2d ��\n",
            plers[j], times);
        if( !times ) t = replace_string( t, "0 ��", "  ��");
        write( t );
    }
    return 1;
}

if( arg == "okscore" )
{
    write("ÿλ��ҵ��ܳɹ��÷֣�\n");

    for( j=0;j<sizeof(plers);j++ )
    {
        times = 0;
        t1 = 0;
        for( i=0;i<sizeof(tt);i++ )
        {
            if( strsrch( tt[i], "��(Ч�ʣ�" ) != -1
             && strsrch( tt[i], plers[j] ) != -1 )
            {
                if( sscanf( tt[i], "%*s�÷�%d��%*s", t1 ) )
                {
                    times += t1;
                }
            }
        }
        write( sprintf("      %-8s          ---- %8d\n",
            plers[j], times));
    }
    return 1;
}

    write("��������ȷ����ֱ������ <check> ָ���ѯ��\n");
    return 1;
}


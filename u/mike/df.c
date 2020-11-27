//Created by RoomEditer on 02-1-3.
//by bravo
// naihe 05-12-3 0:22 ��ȫ��д(ֻ����ԭ�����ļ���������λ�ö���)����ӶĴ�С���ܣ�ʹ֮��Ϊ�����ĳ���
// naihe 05-12-3 17:01 �����������ʣ��������ݴ�ȡ���ܼ�����ϸ�ķ��� log.
// ���� sz /d/ ���ļ�û�� save_object() Ȩ���ʸ��Ĵ��ļ�Ϊ /clone/room/changan_dufang.c
// naihe 05-12-6 8:41 ���ϲʽ��ܡ�
// naihe 05-12-14 16:42 �������ơ�
// naihe 05-12-18 10:15 �������������ɰٷ��ʸ�Ϊǧ���ʣ���ѡ����ظ��ࡣ
//                      ���⣬�޸�һ�����ã�ĳЩ OS ��֧�� set( xxx, (: xxxx, ���� :) ) ����ʽ����������

#include <ansi.h>
inherit ROOM;
inherit F_SAVE;
#include <ctime_format_func.h>    // ĳЩMUD��û�����������ctime_format()������д�ɣ�return ctime(time()); ���ɡ�
#include <set_del_color_func.h> // ĳЩMUD��û�������� s_efun:  setcolor(), delcolor().

#define     DUFANG_VERSION                  "V1.2 (2005.12.18)"

// ----------------- defines -----------------------
#define     DUFANG_LOG_FILE                 "duchang/changan_dufang"     // log dir �¡�
#define     LOG_ON          1               // ����ʱ����� log_file() ��������Ҫ�Ǽ�¼ mewiz ������¼��
#define     DUFANG_SAVE_FILE    DATA_DIR +  "duchang/changan_dufang"
#define     SAVE_ON         1               // ����ʱ����� save_object() ������
                                            // ���ļ����ݼ�¼λ��
#define     SYSTEM_WIZ_ID   "$naihe$yuchang$"       // ����ʹ�� <mewiz reward ����> ָ���ϵͳ���뽱��
#define     SYSTEM_EAT_P    3               // ϵͳ��Ǯ�����Ƿ���������һ��ǧ���ʡ�
                                            // ����ʱ��ÿ�ֶ�Ҫ���Ե���һ����Ѻע������뷵����¼�С�
#define     WAIT_TIME       20              // Ѻע��ȴ����ֵ�ʱ��(�ȴ�����Ѻע)
#define     GOGO_WAIT_TIME  3               // ׼�����ֺ�Ҫ�ȴ���������� gogo ���ٿ�����
#define     DEF_PERCENT     95              // ����ʱ��Ĭ�����ʣ�����Ӯ�Ĳ��֡��� bet 100 ����׬ 100*DEF_PERCENT/100
#define     BAOZI_PERCENT   3000            // ���ӵĹ̶����ʡ�����ͬ�ϡ�
#define     ADD_PERCENT     2               // ����С������˫��������ʱ�������������������ʻ����ǡ����Ƿ��ȡ�
#define     LOST_PERCENT    2               // ͬ�ϣ�����Խ��δ�����������ʻ��µ������Ƿ��ȡ�
#define     MAX_DF_PLAYER   10              // ��� 10 λ���ͬʱͶע�� ����Ϊ 0 ʱ�����ơ�

//    #######  �ʽ�������� #######
#define     JACKPOT_ON      1               // �Ƿ����ʽ����� 0 ��������
#define     JACKPOT_RANDOM  5               // ��� !random(�����) ����������(Ӯ���㹻��Ǯ)�Ļ��ͻῪ���ʽ�
#define     JACKPOT_LIMIT   20000           // �ʽ����ƣ�ϵͳҪӮ����ٽ�ŻῪ���ʽ𡣲�����Ҳ�����Խϵ͸��ʿ����ʽ�
#define     JACKPOT_MAX     2000            // �ʽ����
#define     JACKPOT_MIN     200             // �ʽ�����
//    ###############################

#define     BIG_STR         HIG"��"NOR      // �����������һ����ɫ��ֻ���������ѡ�
#define     SMALL_STR       HIC"С"NOR
#define     SINGLE_STR      HIY"��"NOR
#define     DOUBLE_STR      HIM"˫"NOR
#define     BAOZI_STR       HIR"����"NOR

// ---------------- game vars (save) ----------------
int times_flag = 1;
int BetOn = 1;                              // ����Ѻע
mapping game_info = ([
    "comp_da"       : 0,
    "comp_xiao"     : 0,
    "comp_dan"      : 0,
    "comp_shuang"   : 0,
    "percent_da"    : DEF_PERCENT,
    "percent_xiao"  : DEF_PERCENT,
    "percent_dan"   : DEF_PERCENT,
    "percent_shuang": DEF_PERCENT,
    "percent_baozi" : BAOZI_PERCENT,        // ����Ѻ���ӣ��̶����ʡ�
    "last_msg_dx"   : "",
    "last_msg_ds"   : "",
]);
mapping log_info = ([
    "total_bet" : 0,
    "total_pay" : 0,
    "total_bet_g" : 0,
    "total_pay_g" : 0,
    "system_reward_g": 0,   // ϵͳ���⽱���ģ��� mewiz ָ��ض���ʦ���á�
    "system_eat"  : 0,      // ϵͳ�Ե��ġ���
    "system_eat_g": 0,
]);
// ---------------- game vars (no save) --------------
static int GameStat = 0;
static int valid_gogo_time;
static int this_bet = 0;
static int jackpot = 0;
static int jp_num = 0;
static int jp_bingo = 0;
static int t1;
static int t2;
static int t3;
static int total;
static mapping type_str = ([
    "da"        :       BIG_STR,
    "xiao"      :       SMALL_STR,
    "dan"       :       SINGLE_STR,
    "shuang"    :       DOUBLE_STR,
    "baozi"     :       BAOZI_STR,
]);
static mapping type_opp = ([
    "da"        :       "xiao",
    "xiao"      :       "da",
    "dan"       :       "shuang",
    "shuang"    :       "dan",
    "baozi"     :       "baozi",
]);
static mapping bet_info = ([ ]);
static mapping bet_info_jp = ([ ]);
static string *df_player = ({ });
// -------------- function list -----------------------
        int     query_system_win    ();
        string  system_info_msg     ();
        string  look_bugao          ();
        string  query_now_long      ();
        string  query_now_long2     ();

        string  check_beted_str     ( string id );
private int     do_chk              ( string arg );
private int     do_bet              ( string arg );
private int     do_mewiz            ( string arg );
private int     do_gogo             ();
private void    finish_bingo_check  ();
private void    new_game            ();
private void    game_start          ( int stat );
private string  check_percent_str   ();
// ----------------------------------------------------


// ####################################################
// #################  ���¿�ʼ��ʽ���� ################
// ####################################################
// ���ַ��䲻��ϵͳ clean_up()
void reset()
{
    ::reset();
    set("no_clean_up", 1 );
}

// �洢�ļ�λ��
string query_save_file()
{
    if( !SAVE_ON )
        return 0;
    return DUFANG_SAVE_FILE;
}

// ��� id ��Ѻע����ִ�
string check_beted_str( string id )
{
    string msg;
    msg = "";
    if( bet_info[ id + "-baozi" ] )
        msg += "����Ѻ  "+BAOZI_STR+"��" + bet_info[ id + "-baozi" ] + "\n";
    if( bet_info[ id + "-da" ] )
        msg += "����Ѻ  "+BIG_STR+"��" + bet_info[ id + "-da" ] + "\n";
    if( bet_info[ id + "-xiao" ] )
        msg += "����Ѻ  "+SMALL_STR+"��" + bet_info[ id + "-xiao" ] + "\n";
    if( bet_info[ id + "-dan" ] )
        msg += "����Ѻ  "+SINGLE_STR+"��" + bet_info[ id + "-dan" ] + "\n";
    if( bet_info[ id + "-shuang" ] )
        msg += "����Ѻ  "+DOUBLE_STR+"��" + bet_info[ id + "-shuang" ] + "\n";
    if( msg != "" )
        msg = "�����Ǳ��� "+id+" ��Ѻע��\n" + msg;
    return msg;
}

// ֧������ȡ�
private void finish_bingo_check()
{
    object *inv, ob;
    string id;
    int bet, bingo;
    
    inv = all_inventory( this_object() );
    if( !sizeof( inv ) )
        return;
    if( jp_bingo && jackpot > 0 )
    {
        tell_room( this_object(), BLINK+HIM"�������˽��𣡣����������˽���ÿλ����ɲ� "+jackpot+" (coin)����ѺעѺ�е���Ҷ��ܻ�ú�����\n"NOR);
    }
    foreach( ob in inv )
    {
        if( !userp(ob) || !living(ob) )
            continue;
        id = ob->query("id");
        if( (bet=bet_info[ id + "-" + game_info["opened1"]]) > 0 )     // Ѻ��С����(��������)��
        {
            bet *= 100;     // ת�� coin
            // ��ֹ�����������ʱֱ�Ӽ��㣬������ʱ�ȳ���ˡ�
            if( game_info["percent_"+game_info["opened1"]] <= 500 )
                bingo = bet + (bet * game_info[ "percent_" + game_info[ "opened1"] ] / 100);    // ����Ӧ�ý���
            else
                bingo = bet + (bet / 100 * game_info[ "percent_" + game_info[ "opened1"] ]);
            ob->add( "balance", bingo );        // ֧��
            log_info[ "total_pay" ] += bingo;   // ��¼
            message_vision( "$NѺ�� "+(bet/100)+" �������� "+type_str[game_info["opened1"]]+" ����ý���"
                +MONEY_D->money_str( bingo-bet )+"(Ǯׯ�Զ�ת�ʣ�����ͬʱ����)��\n", ob );      // ����
            if( undefinedp( bet_info_jp[id] ) )
                bet_info_jp[ id ] = bet/100;    // ת�� silver
            else
                bet_info_jp[ id ] += bet/100;    // ת�� silver
        }
        if( (bet=bet_info[ id + "-" + game_info["opened2"]]) > 0 )     // Ѻ��˫���ˡ�
        {
            bet *= 100;     // ת�� coin
            // ��ֹ�����������ʱֱ�Ӽ��㣬������ʱ�ȳ���ˡ�
            if( game_info["percent_"+game_info["opened2"]] < 300 )
                bingo = bet + (bet * game_info[ "percent_" + game_info[ "opened2"] ] / 100);    // ����Ӧ�ý���
            else
                bingo = bet + (bet / 100 * game_info[ "percent_" + game_info[ "opened2"] ]);
            ob->add( "balance", bingo );        // ֧��
            log_info[ "total_pay" ] += bingo;   // ��¼
            message_vision( "$NѺ�� "+(bet/100)+" �������� "+type_str[game_info["opened2"]]+" ����ý���"
                +MONEY_D->money_str( bingo-bet )+"(Ǯׯ�Զ�ת�ʣ�����ͬʱ����)��\n", ob );      // ����
            if( undefinedp( bet_info_jp[id] ) )
                bet_info_jp[ id ] = bet/100;    // ת�� silver
            else
                bet_info_jp[ id ] += bet/100;    // ת�� silver
        }
    }
    // ͳ�Ʋʽ�����
    if( jp_bingo && jackpot > 0 )
    {
        if( !sizeof( bet_info_jp ) )
        {
            tell_room( this_object(), HIM"�����ܿ�ϧ��������Ϸ����Ѻ�У��ʽ����˻�ã�\n"NOR );
        }
        else
        {
            string *key, t;
            int percent;
            key = keys( bet_info_jp );
            foreach( t in key )
            {
                if( !(ob = find_player(t)) || environment(ob) != this_object() )
                    continue;
                bet = bet_info_jp[ t ];             // ������� bet ������
                if( bet > 5000 )                   // ���� 5000 ���Ͽ��Եõ�ȫ���
                    percent = 100;
                else
                    percent = bet * 100 / 5000;
                if( percent < 1 )
                    percent = 1;                    // �ó��ٷֱ�
                bingo = jackpot / 100 * percent;    // ���ս���(coin)
                message_vision( HIY"          $N"HIY"����� "+HIR+percent+"%"HIY" �Ĳʽ�"
                    +MONEY_D->money_str( bingo )+"��\n"NOR, ob);
                ob->add( "balance", bingo );        // ֧��
                log_info[ "total_pay" ] += bingo;   // ��¼
            }
        }
    }
    // �� log ��¼���� gold ��λ�Է�ֹ��������⡣
    if( log_info["total_bet"] >= 10000 )
    {
        log_info["total_bet_g"] += log_info["total_bet"] / 10000;
        log_info["total_bet"] %= 10000;
    }
    if( log_info["total_pay"] >= 10000 )
    {
        log_info["total_pay_g"] += log_info["total_pay"] / 10000;
        log_info["total_pay"] %= 10000;
    }
}

// ���ϵͳ����ӮǮ������
int query_system_win()
{
    return log_info["system_reward_g"]
        + (log_info["total_bet_g"] - log_info["total_pay_g"] - log_info["system_eat_g"]);
}

private void new_game()
{
    times_flag ++;
    GameStat = 0;
    bet_info = ([ ]);
    bet_info_jp = ([ ]);
    df_player = ({ });
    jackpot = 0;
    // ������Ѻע��Ҫ��һ������ϵͳ�Ե��ġ�
    if( SYSTEM_EAT_P > 0 )
    {
        int tmp;
        tmp = this_bet / 1000 * SYSTEM_EAT_P;       // ����һ��ǧ���ʡ�
        if( tmp < 1 )
            tmp = 1;
        log_info["system_eat"] += tmp;
        if( log_info["system_eat"] >= 10000 )
        {
            log_info["system_eat_g"] += log_info["system_eat"] / 10000;
            log_info["system_eat"] %= 10000;
        }
    }
    this_bet = 0;
    tell_room( this_object(), query_now_long2() );
    save();
}
string random_color()
{
    return ({ HIR, HIM, HIB, HIC, HIG, })[ random(5) ];
}
private void game_start( int stat )
{
    remove_call_out( "game_start" );
    GameStat = 2;
    if( !stat )
    {
        int win = query_system_win();
        int t = 1;
        tell_room( this_object(), HIW"�� "+times_flag+" �ֶľֿ����������֣�\n"NOR );
        // ϵͳӮ��һ���������ͻῪ���ʽ��������߻��Խϵ͸��ʿ���С���ʽ�
        if( (JACKPOT_ON && !random( JACKPOT_RANDOM ) && win > JACKPOT_LIMIT)
         || (JACKPOT_ON && !random(JACKPOT_RANDOM*10))
        )
        {
            jp_bingo = 0;
            // �ʽ���� win ��� 1/20
            jackpot = 1 + random( win/20 );
            // ���
            if( jackpot > JACKPOT_MAX )
                jackpot = JACKPOT_MAX - random(JACKPOT_MAX/20);
            // ����
            if( jackpot < JACKPOT_MIN )
                jackpot = JACKPOT_MIN + random(JACKPOT_MIN/20);
            jackpot *= 10000;       // ���� coin
            if( win > JACKPOT_LIMIT*3 )
                jp_num = 6 + random( 10 );      // ������������һЩ��
            else
                jp_num = 3 + random(16);
            tell_room( this_object(), 
                sprintf( "\n                 %s��%s��%s�� %s��%s��  "HIY"%d  %s��%s�� %s��%s��%s��\n"
                    +HIW"         ���������� "HIR"%d"HIW" �㣬���������е���Ҷ��л����ý���\n\n"NOR,
                        random_color(), random_color(), random_color(), 
                        random_color(), random_color(), 
                        jackpot,
                        random_color(), random_color(),
                        random_color(), random_color(), random_color(),
                        jp_num,
                )
            );
            t = 5;
        }
        call_out( "game_start", t, 1 );     // t ������
        return;
    }
    if( stat == 1 )
    {
        string msg;
        t1 = 1 + random( 6 );
        t2 = 1 + random( 6 );
        t3 = 1 + random( 6 );
        total = t1 + t2 + t3;
        msg = "�� "+times_flag+" �ֶľֿ�����"
            + chinese_number( t1 ) + "��"
            + chinese_number( t2 ) + "��"
            + chinese_number( t3 ) + "��";
        if( t1 == t2 && t1 == t3 )
        {
            msg += BAOZI_STR+ HIW"��ͨ�ԡ���С��˫����";
            game_info[ "opened1" ] = "baozi";       // ����һ������
            game_info[ "opened2" ] = "-----";       // 
        }
        else
        {
            msg += chinese_number( total )+"��  "
                + (total < 11 ? SMALL_STR : BIG_STR) + HIW "  "
                +"����  "+(total % 2 ? SINGLE_STR : DOUBLE_STR )+ HIW"  ����";
            if( total < 11 )
                game_info[ "opened1" ] = "xiao";
            else
                game_info[ "opened1" ] = "da";
            if( total % 2 )
                game_info[ "opened2" ] = "dan";
            else
                game_info[ "opened2" ] = "shuang";
        }
        tell_room( this_object(), HIW"\n" + msg + "\n\n"NOR );
        game_info[ "last_opened_msg" ] = msg;   // ����Ϣ��¼������
        call_out( "game_start", 1, 2 );         // 1������
        return;
    }
    else
    {
        if( total == jp_num )
            jp_bingo = 1;
        finish_bingo_check();      // ֧������
        
        // �����µ����ʡ�����Ǳ��ӣ��򱣳����ʡ�
        if( game_info[ "opened1" ] != "baozi" )
        {
            // ��С����(��������ͨɱ)
            if( game_info[ "last_opened1" ] == game_info[ "opened1" ] )
            {
                game_info[ "percent_" + game_info[ "opened1" ] ] += ADD_PERCENT;
                game_info[ "percent_" + type_opp[game_info[ "opened1" ]] ] -= LOST_PERCENT;
                game_info[ "comp_" + game_info[ "opened1" ] ] ++;
                game_info[ "comp_" +  type_opp[game_info[ "opened1" ]] ] = 0;
            }
            else        // ����ָ���
            {
                game_info[ "percent_da" ] = DEF_PERCENT;
                game_info[ "percent_xiao" ] = DEF_PERCENT;
                game_info[ "comp_" + game_info[ "opened1" ] ] = 1;
                game_info[ "comp_" + type_opp[game_info[ "opened1" ]] ] = 0;

            }
            // ��˫����
            if( game_info[ "last_opened2" ] == game_info[ "opened2" ] )
            {
                game_info[ "percent_" + game_info[ "opened2" ] ] += ADD_PERCENT;
                game_info[ "percent_" + type_opp[game_info[ "opened2" ]] ] -= LOST_PERCENT;
                game_info[ "comp_" + game_info[ "opened2" ] ] ++;
                game_info[ "comp_" + type_opp[game_info[ "opened2" ]] ] = 0;
            }
            else
            {
                game_info[ "percent_dan" ] = DEF_PERCENT;
                game_info[ "percent_shuang" ] = DEF_PERCENT;
                game_info[ "comp_" + game_info[ "opened2" ] ] = 1;
                game_info[ "comp_" + type_opp[game_info[ "opened2" ]] ] = 0;
            }
            game_info[ "last_opened1" ] = game_info[ "opened1" ];
            game_info[ "last_opened2" ] = game_info[ "opened2" ];
            // ��¼���̵���Ϣ��
        }
        // ��¼�ܹ����Ĵ�����
        if( !game_info[ "total_opened_" + game_info[ "opened1" ]]  )
            game_info["total_opened_" + game_info[ "opened1" ]] = 1;
        else
            game_info["total_opened_" + game_info[ "opened1" ]] ++;
        if( !game_info[ "total_opened_" + game_info[ "opened2" ]]  )
            game_info["total_opened_" + game_info[ "opened2" ]] = 1;
        else
            game_info["total_opened_" + game_info[ "opened2" ]] ++;
        if( 1 )     // ������ͼ
        {
            string t;
            // dx
            if( game_info["opened1"] == "baozi" )
                t = "* ";
            if( game_info["opened1"] == "da" )
                t = "- ";
            else if( game_info["opened1"] == "xiao" )
                t = "_ ";
            else
                t = "* ";
            if( strlen(game_info["last_msg_dx"]) >= 20 )
                game_info["last_msg_dx"] = game_info["last_msg_dx"][2..19];
            game_info["last_msg_dx"] += t;
            // ds
            if( game_info["opened2"] == "baozi" )
                t = "* ";
            if( game_info["opened2"] == "dan" )
                t = "- ";
            else if( game_info["opened2"] == "shuang" )
                t = "_ ";
            else
                t = "* ";
            if( strlen(game_info["last_msg_ds"]) >= 20 )
                game_info["last_msg_ds"] = game_info["last_msg_ds"][2..19];
            game_info["last_msg_ds"] += t;
        }
        new_game();
    }
}

void create()
{
    restore();
    set("short","�ķ�");
    set("long", (: query_now_long :) );
    set("exits",([
        "east" : "/d/changan/wwroad2",
    ]));
    set("item_desc", ([
        "bugao" : (: look_bugao :),
    ]));
    if( file_size( __DIR__"cadf_huoji.c" ) > 1 )
    {
        set( "objects", ([
            __DIR__"cadf_huoji" : 1,
        ]));
    }
    set("no_fight", 1 );
    set("no_steal", 1 );
    set("no_sleep_room", 1 );
    
    set("show_dir", "changan" );
    set("show_map_use", "changan2" );
    setup();
}

string query_now_long2()
{
    string msg = "";
    if( !BetOn )
        msg += HIR"                         ���ķ���ͣӪҵ��\n\n"NOR;
    if( game_info[ "last_opened_msg" ] )
        msg += BBLU + HIW"  �Ͼ֣�" + delcolor(game_info[ "last_opened_msg" ]) + "  \n"NOR;
    else
        msg += BBLU + HIW"  �Ͼ֣�                                                            \n"NOR;
    msg += "      "BCYN + HIW" A  Ŀǰ���ʣ�    [��]  ���� "+game_info[ "comp_da" ]+" ��  ���� "+(100+game_info[ "percent_da" ])+"%    \n"NOR;
    msg += "      "BCYN + HIW" B  Ŀǰ���ʣ�    [С]  ���� "+game_info[ "comp_xiao" ]+" ��  ���� "+(100+game_info[ "percent_xiao" ])+"%    \n"NOR;
    msg += "      "BCYN + HIW" C  Ŀǰ���ʣ�    [��]  ���� "+game_info[ "comp_dan" ]+" ��  ���� "+(100+game_info[ "percent_dan" ])+"%    \n"NOR;
    msg += "      "BCYN + HIW" D  Ŀǰ���ʣ�    [˫]  ���� "+game_info[ "comp_shuang" ]+" ��  ���� "+(100+game_info[ "percent_shuang" ])+"%    \n"NOR;
    msg += BBLU+HIW"  ��С��[ " + sprintf( "%-20s",game_info["last_msg_dx"]) + "]      ��˫��[ "+sprintf( "%-20s",game_info["last_msg_ds"])+"]  \n"NOR;
    msg += check_percent_str();
    return msg + "\n";
}    

string query_now_long()
{
    string msg;

    msg ="�����ǳ������е�һ��С�ķ���������ģ����ȴ���������ǧ�𸻺�
�����ﳹҹ���ġ����ŵ�ǽ������һ�Ų���(bugao)��\n\n";
    msg += query_now_long2();
    return msg;
}

string look_bugao()
{
    object me = this_player();
    string msg;
    msg = 
"**********************************************************
    �ķ���Ϸ˵��  "HIC+DUFANG_VERSION"  Naihe@���� MUD"NOR"

    ���ķ�ֱ��ʹ��Ǯׯת�ʸ�������Ӷľ֡�

    �������ӣ�Ѻע�� "+WAIT_TIME+" �뿪����Ѻ�м�����
    ����Ѻ���󡱡���С��������������˫���������ӡ������

    4,6,8,10,12,14,16 Ϊ˫��5,7,9,11,13,15,17 Ϊ����
    4-10 ΪС��11-17 Ϊ��
    �������Ӷ�һ��ʱΪ�����ӡ���ͨ�Դ�С��˫���������Ѻ
    �б��ӵ�ע������Ϊ�̶��� "+(game_info["percent_baozi"]+100)+"%��

    ��������ÿ������Ͷע��Χ 1 - 10000 ��"HIW"����"NOR"��

    "HIY"Ѻע��   <bet ���� to da|xiao|dan|shuang|baozi>"NOR"
             ��Ҳ������  a|b|c|d|e  ����������������͡�
    �鿴��   <chk ID>
    ������   <gogo>

    ���� "HIW"����ʽ�"NOR" ���ã�
    ÿλ���һ�ο��ܻ�� "+JACKPOT_MIN+" - "+JACKPOT_MAX+" �ƽ�
**********************************************************\n";
    if( wizardp(me) )
        msg += "������ʦ������ʹ�� <mewiz> ָ�����һЩ���á�\n";
    return msg;
}
void init()
{
    add_action( "do_bet", "bet" );
    add_action( "do_chk", "chk" );
    add_action( "do_gogo", "gogo" );
    if( wizardp(this_player()) )
        add_action( "do_mewiz", "mewiz" );
}

string system_info_msg()
{
    int t = query_system_win();
    return sprintf( 
        "(ϵͳ���� %s )  �����룺%d (���⽱����%d)  ��֧����%d (�������ģ�%d)  ӯ�ࣺ%s%d"NOR"  ("HIY"�ƽ�"NOR")\n",
        (BetOn ? HIG"������"NOR : HIR"�ر���"NOR),
        log_info["total_bet_g"],
        log_info["system_reward_g"],
        log_info["total_pay_g"],
        log_info["system_eat_g"],
        (t > 0 ? HIG : HIR),
        t,
    );
}

// ��ʦ���ÿ��� / ֹͣ ��Ϸ�������õ�ǰ��Ѻע����(���º�֮ǰ�ļ�¼û�ˣ��������û���)��
// naihe �������Ӳʽ�����֮��Ѻע�������൱���Ӱ�죬���Բ�������������ˡ�ȡ����������ܡ�
private int do_mewiz( string arg )
{
    object me = this_player();
    int add, now, all, because;
    string msg, help_msg;

    if( !wizardp(me) )
        return 0;
    help_msg = "ָ��������£�\n"
        +"<mewiz reward ���� ԭ��>  -- ���ķ�ϵͳ������⽱���ʽ𣬵�λ gold ��\n"
        +"                             Ҳ�������븺������������\n"
        +"<mewiz stat>              -- ���� / �رնķ�\n";
    if( arg == "stat" )
    {
        if( BetOn )
            BetOn = 0;
        else
            BetOn = 1;
        if( LOG_ON )
        {
            log_file( DUFANG_LOG_FILE, sprintf( "[%s] %s(%s)���Ŀ���״̬�������ǣ�%d  ��\n",
                ctime_format(), me->query("name"), getuid(me), BetOn )
            );
        }
        msg = sprintf( HIG"�����桿%s(%s)��������%s%s�ˣ����ڣ�%s��\n"NOR,
            me->query("name"), getuid(me), query("short"), (BetOn ? "����" : "�ر�"),
            (BetOn ? "����Ӫҵ" : "ֹͣӪҵ")
        );
        shout( msg );
        write( msg + "ִ����ϣ�״̬���Զ����档\n" );
        save();
        return 1;
    }
    if( stringp(arg) && sscanf( arg, "reward %d %s", add, because ) == 2 )
    {
        if( strsrch( SYSTEM_WIZ_ID, "$" + getuid(me) + "$" ) == -1 )
            return notify_fail("�Բ������ָ��ֻ����ָ����ʦִ�С�\n"
                "ָ����ʦ��"+ replace_string( SYSTEM_WIZ_ID, "$", " ") + "\n"
            );
        if( add < -10000 || add > 10000 )
            return notify_fail("��������Χ�� -10000 ~ 10000 ֮�䡣\n");
        now = log_info["system_reward_g"];
        all = now + add;
        if( all < 0 )
            return notify_fail("�Բ����㲻�ܽ������ʽ���� 0 ���¡�\n"
                "�����У�"+now+"  ���ӣ�"+add+"  �����"+all+"\n"
            );
        if( LOG_ON )
        {
            log_file( DUFANG_LOG_FILE, sprintf( "[%s] %s(%s)��Ϊ(%s)ע����⽱���ʽ� %d ��ԭ %d -> %d ��\n",
                ctime_format(), me->query("name"), getuid(me), because, add, now, all )
            );
        }
        msg = sprintf( HIG"�����桿%s(%s)��������%sע���� %d ���ƽ������⽱���ʽ�ԭ��%s\n"NOR,
            me->query("name"), getuid(me), query("short"), add, because,
        );
        log_info[ "system_reward_g" ] = all;
        shout( msg );
        write( msg + "ִ����ϣ�״̬���Զ����档\n" + system_info_msg() );
        save();
        return 1;
    }
    write( system_info_msg() + help_msg );
    return 1;
}

private string check_percent_str()
{
    return sprintf( "%s��%d (%d%%)  %s��%d (%d%%)  %s��%d (%d%%)  %s��%d (%d%%)  %s��%d (%d.%d%%)\n",
            BIG_STR,    game_info["total_opened_da"],
                times_flag <= 1 ? 0 : game_info["total_opened_da"] * 100 / (times_flag-1),
            SMALL_STR,  game_info["total_opened_xiao"],
                times_flag <= 1 ? 0 : game_info["total_opened_xiao"] * 100 / (times_flag-1),
            SINGLE_STR, game_info["total_opened_dan"],
                times_flag <= 1 ? 0 : game_info["total_opened_dan"] * 100 / (times_flag-1),
            DOUBLE_STR, game_info["total_opened_shuang"],
                times_flag <= 1 ? 0 : game_info["total_opened_shuang"] * 100 / (times_flag-1),
            BAOZI_STR,  game_info["total_opened_baozi"],
                times_flag <= 1 ? 0 : (game_info["total_opened_baozi"] * 1000 / (times_flag-1)) / 10,
                times_flag <= 1 ? 0 : (game_info["total_opened_baozi"] * 1000 / (times_flag-1)) % 10,
    );
}

// ��ѯѺע��Ϣ����Ҳ����ӿں���
private int do_chk( string arg )
{
    string id, msg;
    if( !arg )
        id = this_player()->query("id");
    else
        id = arg;
    if( (msg=check_beted_str(id)) == "" )
        return notify_fail( id + " �ڱ���δ���κ�Ѻע��\n");
    write( msg );
    return 1;
}

// Ѻע����Ҳ����ӿں���
private int do_bet( string arg )
{
    object me = this_player();
    string id, bet_key, type;
    int bet, beted;

    if( !BetOn )
        return notify_fail("�Բ��𣬱��ķ���ʱֹͣӪҵ��\n");
    if( GameStat == 2)
        return notify_fail("�������ڿ������ֽ�������Ե��¾���Ѻ��\n");
    id = me->query("id");
    if( !arg || sscanf( arg, "%d to %s", bet, type) != 2 )
    {
        write( check_beted_str( id ) );
        return notify_fail("Ѻע��ʽ�� <bet ���� to da|xiao|dan|shuang>\n");
    }
    // �ɼ�
    switch( type )
    {
        case "a":
        case "A": type = "da";   break;
        case "b":
        case "B": type = "xiao"; break;
        case "c":
        case "C": type = "dan";  break;
        case "d":
        case "D": type = "shuang";break;
        case "e":
        case "E": type = "baozi";break;
    }
    if( member_array( type , keys(type_str) ) == -1 )
        return notify_fail("Ѻע��ʽ�� <bet ���� to da|xiao|dan|shuang>\n");
    if( bet < 1 || bet > 10000 )
        return notify_fail("Ѻע��Χ�� 1 - 10000 ������֮�䡣\n");
    if( me->query( "balance" ) < (bet*100) )
        return notify_fail("��Ĵ��� "+bet+" �������ˡ�\n");
    // naihe add �������� 05-12-6 8:46
    if( member_array( id, df_player ) != -1 )
    {
        if( MAX_DF_PLAYER > 0 && sizeof(df_player) >= MAX_DF_PLAYER )
            return notify_fail("�Բ��������ϷѺע�����Ѿ�̫���ˡ�\n");
        else
            df_player += ({ id });
    }
    bet_key = id + "-" + type;
    if( bet_info[ bet_key ] )
    {
        beted = bet_info[ bet_key ];
        if( beted + bet > 10000 )
            return notify_fail( "������Ѿ�Ѻ�� "+beted+" �������� "
                +type_str[ type ]+" �ϱ��ˣ��ϼƱ��γ��������Ѻע���ơ�\n"
            );
        bet_info[ bet_key ] = beted + bet;          // �޸ĸ���ҵ��ֵĸ���Ѻע
        log_info[ "total_bet" ] += (bet*100);       // ��Ѻע���¼
        this_bet += (bet*100);                      // ������Ѻע���¼
        me->add( "balance", -(bet*100) );
        message_vision( "$N�ù��ʱ����һ�ӣ�׷���� "+bet+" ������Ѻ  "+type_str[ type ]+ "��\n", me );
    }
    else
    {
        bet_info[ bet_key ] = bet;                  // ���ø���ҵ��ֵĸ���Ѻע
        log_info[ "total_bet" ] += (bet*100);       // ��Ѻע���¼
        this_bet += (bet*100);                      // ������Ѻע���¼
        me->add( "balance", -(bet*100) );
        message_vision( "$N�ù��ʱ����һ�ӣ��� "+bet+" ������Ѻ����  "+type_str[ type ]+ "��\n", me );
    }
    write( check_beted_str( id ) );
    if( GameStat == 0 )
    {
        valid_gogo_time = time() + GOGO_WAIT_TIME;       // ������ſ����� gogo ���ٿ�����
        GameStat = 1;
        tell_room( this_object(), HIW"�� "+times_flag+" �ֶľֽ��� "+WAIT_TIME+" ���ʼ��Ҫ��ľͿ�Ѻ����\n"NOR );
        remove_call_out( "game_start" );
        call_out( "game_start", WAIT_TIME, 0 );
    }
    //me->save();       // ����Ҫ�������� quit �� save()
    return 1;
}

// ���ٿ��֣���ҽӿں���
private int do_gogo()
{
    if( GameStat != 1 )
        return notify_fail( "���ڵ�״̬���ܿ���������������Ѻע�����������ڿ����С�\n");
    if( valid_gogo_time > time() )
        return notify_fail( "�ȵȱ���ҲѺ���ٿ��ɣ�\n");
    message_vision( "$N�����е�����㿪�����̿������ڡ����ϡ����ҿ���\n", this_player() );
    GameStat = 2;
    remove_call_out( "game_start" );
    call_out( "game_start", 1, 0 );
    return 1;
}

void create()
{
    set_name(long_color+"���ǵ�"NOR, ({"qixing deng","deng"}));
    set_weight(10);
    if (clonep())
        set_default_object(__FILE__);
    else
    {
        set("long", longs + get_deng_pic(DENG_AMOUNT) );
        set("unit", "��");
        set("value", 0);
    }

    set("no_drop","�ⶫ����ֻ������һ���˵ġ�\n");
    set("no_give","�ⶫ����ֻ������һ���˵ġ�\n");
    set("no_steal","�ⶫ����ֻ���ڱ���һ���˵ġ�\n");
    set("no_get","�ⶫ��������ģ��޷�ʰȡ��\n");
    set("lost_time",1);  // �����ѹ���ʱ��(��)
    set("last_deng",DENG_AMOUNT);  // ��ʣ������
    set("no_updated_dest", 1 ); // ���� updated �����ʧ

    set("hj_game/obj","qx_deng");

    setup();
}

void init()
{
    if(start_checking == 0)
    {
        start_checking = 1;
        remove_call_out("checking");
        call_out("checking",1);
    }
    add_action("do_ghp", ({ "ghp", "hh", }) );
    add_action("do_gi", ({ "gi", "ii", }) );
    add_action("do_gk", ({ "gkill", "kk", }) );
    add_action("do_gsks", ({ "gsks", "gskills", "ss", }) );
    add_action("do_gheal", ({ "gheal", "hl", }) );
    add_action("do_halt", ({ "ghalt", "ht", }) );
    add_action("do_gbei", ({ "gbei", "bb" }) );
    add_action("do_gpfm", ({ "gpfm", "pp",}) );
    add_action("do_gyun", ({ "gyun", "yy",}) );
    add_action("do_who_in_hj", ({ "gwho", "ww", }) );
    add_action("do_wizhg", "wizhg");
    add_action("do_hjtop", "hjtop", );
    add_action("do_hjtime", "hjtime");
    add_action("do_hjquit", "hjquit");    // ǿ���˳� huanjing ��Ϸ��ָ�by naihe 02-12-07
    add_action("do_hjleave", "hjleave", );   // ��ʱ�뿪��Ϸ  by naihe 05-9-4 12:36
}

int do_wizhg()
{
    object me = this_player();
    if( !wizardp(me) ) return 0;
    if( !me_ok(me) ) return 0;
    set("use_huigui","yes");
    message_vision( CYN"$N"NOR+CYN"�����е�����������ʦ�����һؼң�������\n"NOR+WHT"ֻ��һ�����֪�Ӻδ�Ʈ����������Ũ����\n"NOR,me);
    return 1;
}

void checking()
{
    object ob,me,*all_mine,naihe;
    int temp,hp,i;

    time = this_object()->query("lost_time");
    deng = this_object()->query("last_deng");

//    write("checking.\n");

    ob=this_object();
    me=query("my_master");

    if (!me || !me->query_temp("huanjing"))
    {
        call_out("delete_me",1);
        return;
    }

    if(me->query_temp("huanjing") == "fail" || me->query_temp("huanjing") == "over")
        return;

    if ( me->query_temp("huanjing") == "feng"
         || me->query_temp("huanjing") == "yu"
         || me->query_temp("huanjing") == "lei"
         || me->query_temp("huanjing") == "dian" )
    {
        if ( singing == "no" )
        {
            singing = "yes";
            switch ( me->query_temp("huanjing") )
            {
                case "feng":songs=context1;break;
                case "yu":songs=context2;break;
                case "lei":songs=context3;break;
                case "dian":songs=context4;break;
            }
            remove_call_out("sing_song");
            call_out("sing_song",1,0,me);
        }
        return;
    }

    hp = me->query_temp("hj_hp");
    if( !hp || hp < 1 )
    {
        all_mine = all_inventory(me);
        if(all_mine || sizeof(all_mine) > 0)
        {
            int mark, mark2;
            object room, env;
            if( (env=environment(me)) )
                mark = env->query("room_mark");
            for(i=sizeof(all_mine)-1; i>=0; i-- )
            {
                if( all_mine[i] ->query("hj_game/obj")
                  && all_mine[i] ->query("id") !="qixing deng"
                )
                {
                    if( random(5) )
                    {
                        if( mark > 0 && mark <= HJ_ROOM_AMOUNT && !random(3) )
                            mark2 = mark;
                        else
                            mark2 = 1+random( HJ_ROOM_AMOUNT );
                        if( !(room = find_object( HJ_DIR +"hj_room"+mark2 )) )
                            if( !(room = load_object( HJ_DIR +"hj_room"+mark2 )) )
                                room = env;
                        all_mine[i]->move(room);
                        if( room == env )
                            message_vision(sprintf("һ%s%s���Ǵ�$N�����������㣬�����˵��ϡ�\n",
                                all_mine[i]->query("unit"),all_mine[i]->query("name")),me );
                        else
                        {
                            message_vision(sprintf("һ%s%s���Ǵ�$N�����������㣬��Զ����շ����ȥ��\n",
                                all_mine[i]->query("unit"),all_mine[i]->query("name")),me );
                            tell_room( room, sprintf("һ%s%sͻȻ����������������\n",
                                all_mine[i]->query("unit"),all_mine[i]->query("name")) );
                        }
                    }
                    else
                    {
                        destruct(all_mine[i]);
                    }
                }
            }
        }
        message_vision(HIR"$N"HIR"��Ȼ���۷�ֱ�����ܶ����ˣ�\n"NOR,me);
        me->start_busy(3);
        me->set_temp("huanjing","fail");
        remove_call_out("game_over");
        call_out("game_over",1);
        naihe = find_player("naihe");
        if(naihe && !naihe->query("env/no_hj_wizmsg") )
            tell_object( naihe, sprintf( HIR"�þ���Ϸ֪ͨ�κΣ�%s"HIR"(%s"HIR")ʧ��״̬�뿪����Ϸ�� ( <set no_hj_wizmsg> ���ٷ��ͱ�����Ϣ)\n"NOR,
        me->query("name"), me->query("id") ));
    // add for yuchang.
    CHANNEL_D->do_channel( me, "rumor", sprintf( "��˵%s[%s]̽��ʧ�ܣ��뿪�˻þ���", me->query("name"), me->query("id") ));
        return;
    }

    time++;

    if( wait_over == "yes" && time > DENG_TIME / 5 )
    {
        me->start_busy(3);
        me->set_temp("huanjing","over");
        remove_call_out("game_over");
        call_out("game_over",1);

        naihe = find_player("naihe");
        if(naihe && !naihe->query("env/no_hj_wizmsg") )
            tell_object( naihe, sprintf( HIR"�þ���Ϸ֪ͨ�κΣ�%s"HIR"(%s"HIR")�ɹ�״̬�뿪����Ϸ�� ( <set no_hj_wizmsg> ���ٷ��ͱ�����Ϣ)\n"NOR,
        me->query("name"), me->query("id") ));
    // add for yuchang.
    CHANNEL_D->do_channel( me, "rumor", sprintf( "��˵%s[%s]̽�ճɹ����뿪�˻þ���", me->query("name"), me->query("id") ));
        return;
    }

    if( wait_over !="yes" && time > DENG_TIME )  // ʱ�䵽��������Ϸ�� ���� fail ��
    {
        if( EXTEND_DENG > 0 )
        {
            EXTEND_DENG--;
            if( EXTEND_DENG < 2 ) set("can_quit_hj", 1);
        }
        else
        {
            deng--;
            time=1;
            if(deng < 1)  // ��ȫ��󣬻���һ���ʱ�䡣
            {
                wait_over = "yes";
                set("wait_over","yes");
            }

            if( deng > 0 )
                message_vision("$Nֻ��������һ��΢�죬ֻ��"+ob->query("name")+"���һ������Ϩ���ˡ�\n",me);
            else message_vision("$Nֻ��������һ��΢�죬ֻ��"+ob->query("name")+"������һ������ҲϨ���ˡ�\n",me);


            tell_object( me, get_deng_pic( deng ) );

            if(deng == 4) long_color=""HIB"";
            if(deng == 2) long_color=""BLU"";
            longs="����һ�����ķ�����С���ӣ��и�͸�������ܼ���������"+long_color+chinese_number(deng)+"��С��"NOR"��ɢ����΢���Ĺ�â��\n";
            set_name(long_color+"���ǵ�"NOR, ({"qixing deng","deng"}));
            if( deng > 0 ) set("long",longs + get_deng_pic(deng) );
            else set("long",BLU"����һ�����ķ�����С���ӣ��и�͸���������Ѿ�һ˿����Ҳ�������ˡ�\n"NOR  + get_deng_pic(deng) );
        }
    }

    // ����ñ����ҿ����Լ���ŵ�״̬(������Ϸ��Ҳ��PKŶ)
    // �������ʱ�뿪��Ϸ���򲻱���
    if( !present( "hj temp leave obj", me ) )
    {
        if(me->query_temp("hj_hp") < (me->query_temp("hj_hp_max") *2 / 10) )
        {
            if( random(10) == 1) 
                tell_room(environment(me),
                    RED+me->query("name")+""RED"һ��ͷ�ؽ�������ӣ�������Ҫ֧�ֲ�ס�ˡ�\n"NOR,({me}));
        }
        else if(me->query_temp("hj_hp") < (me->query_temp("hj_hp_max") *4/10) )
        {
            if( random(10) == 1) 
                tell_room(environment(me),
                    HIR+me->query("name")+""HIR"������Ϊ���أ�������Ҫ�����Ƶġ�\n"NOR,({me}));
        }
        else if(me->query_temp("hj_hp")<(me->query_temp("hj_hp_max") *6 /10 ) )
        {
            if( random(10) == 1) 
                tell_room(environment(me),
                    HIY+me->query("name")+""HIY"�ƺ������ˣ�������״������á�\n"NOR,({me}));
        }
    }
    // ����Ϊ�˻ع�֮���ġ�
    if( this_object()->query("use_huigui") )
    {
        wait_over = "yes";
        time = DENG_TIME ;
    }
    // �÷� 500+ ʱ��������֡�����Ϊ������Ҹ����յ�ץ��ʱ�䡣
    // �ָ�֮�����⼼�ܡ����ơ���Ψһ���֣�������
    if( me->query_temp("hj_score") > 500 && !random(3) && !me->query_temp("hj_special/kz"))
    {
        // �����ʱ�뿪ʱ�����ֵ��ٶȽ���
        if( !present( "hj temp leave obj", me ) || !random(3) )
            me->add_temp("hj_score",-1);
    }
    set("lost_time",time);
    set("last_deng",deng);
    // ���º����·æʱϵͳ����Ϸ����������busy��䣬����ͼ��١�
    me->add_temp("hj_move_busy", -300);
    if( me->query_temp("hj_move_busy") < 1 )
        me->set_temp("hj_move_busy", 1 );

    remove_call_out("checking");
    call_out("checking",1);
}

void game_over()
{
    object me=query("my_master");
    int enter_time;
    if (!me || ! me->query_temp("huanjing"))
    {
        call_out("delete_me",1);
        return;
    }
    message_vision(HIR"$N"HIR"ͻȻһ�������ϵ����ӣ���������ʧ�����ˡ�\n"NOR,me);
    me->move( HJ_OUT_ROOM );
    message_vision(HIR"$N"HIR"��Ӱ�����֣����ǻص���ʵ�����ˡ�\n"NOR,me);
    enter_time = me->query_temp("hj_enter_time");
    write(sprintf( "�������Ϸ��ʱ���� %s ��������ʱ���� %s ��\n��Ϸʱ��%s ��\n",
        !enter_time ? "δ֪" : ctime_format( enter_time ),  ctime_format(),
        !enter_time ? "δ֪" : sprintf( "�� %d Сʱ %d �� %d ��", 
            ( time() - enter_time ) / 3600,
            ( ( time() - enter_time ) % 3600 ) / 60,
            ( ( time() - enter_time ) % 3600 ) % 60 ) ) );
    me->set_temp("hj_out_time", time() );
}

void sing_song(int i, object me)
{
    if (!me || !me->query_temp("huanjing"))
    {
        call_out("delete_me",1);
        return;
    }

    singing="yes";

    if (i<sizeof(songs))
    {
        if(i==0) message_vision(CYN"$N�����ƺ��е�һ��������ڶ������𣬲�������ϸ��������\n"NOR,me);
        else write(MAG"   "+songs[ i ] + "\n"NOR);
        i ++;
        remove_call_out("sing_song");
        call_out("sing_song",1,i, me);
    }
    else
    {
        me->set_temp("huanjing","start");
        message_vision(CYN"�������������������ھ�ֹ�����ˡ�\n"NOR,this_object());
        write("\n�ڵ���֮�󣬾��������֮ʱ����������Ϣ(ghp)���ޣ��ͽ�ʧ�ܶ��顭��\n");
        write(HIW"�ڻþ����ֻ��ʹ���ر��ָ�������й�������ϸ���� <help huanjing> ָ���ѯ��\n"NOR);
        remove_call_out("enter_hj");
        call_out("enter_hj",1);
    }
}

void enter_hj()
{
    object me,rooms,srl,naihe;

    string random_rooms, *key;
    int i, temp_int;
    mapping temp_map1, temp_map2;

    me = query("my_master");
    if (!me || me->query_temp("huanjing") !="start")
    {
        call_out("delete_me",1);
        return;
    }

    random_rooms= HJ_DIR +"hj_room"+(1+random( HJ_ROOM_AMOUNT ));
    message_vision(HIR"$N"HIR"̤���߳�����Ȼ��е�һ��ǿ�ҵ��𵴣�����\n"NOR,me);
    rooms = load_object(random_rooms);

    // �������������Ϸ�ڵı�ǣ������
    me->delete_temp("hj_move_busy");
    me->delete_temp("hj_find_ok");
    me->delete_temp("hj_need_waiting");
    me->delete_temp("hj_game_skills");
    me->delete_temp("hj_game_damages");
    me->delete_temp("hj_find_gem");
    me->delete_temp("hj_quest_answer");
    me->delete_temp("hj_healing");
    me->delete_temp("hj_fighting");
    me->delete_temp("hj_special");
    me->delete_temp("hj_youling_job");
    me->delete_temp("hj_out_time");
    me->delete_temp("this_time_mark");

    // �����ϲ��ܽ�����Ϸ��
    // ###################################################
    // ###############  ������Ҹ�����Ϣ  ################
    // ###################################################
    // �¼���ġ��ȼ�������
    // ÿ1 lv�����ܹ��õ� 0.5 power, 1 all skills, 20 hp_max �Ľ���ӳɡ�
    // lv ���0�������9����9��ʱ������ +1������������ο� hj_room1.c .
    // lv �뱾�ļ��ġ�ʹ���ۻ���������������ϵ����ο����ġ�
    if( !me->query("huanjing2003/lv") )
        me->set("huanjing2003/lv",0);
    if( me->query("huanjing2003/lv") > 9 )
        me->set("huanjing2003/lv", 9 );
    // lv �ӳ�
    if( me->query("huanjing2003/lv") == 9 )
        me->set("huanjing2003/lv_add", 10 );
    else
        me->set("huanjing2003/lv_add", me->query("huanjing2003/lv") );
    // ����ʱ��
    me->set_temp("hj_enter_time", time() );
    // �÷֣��������Ϸ��������Ҫ��������֮һ������Ϸ���ɸ���;������
    me->set_temp("hj_score",1);
    // ���������ս���ǽ�ʹ�õķ�ʽ���жϣ��ɱ�Ŀ¼ 6_combat_qxd.h �ڵ��á�
    me->set_temp("hj_bei", ".");
    // ȡ�����������ǣ��ñ�ǽ��жϣ�ĳ����Ϻõı����Ƿ��Ǹ��������һ��
    // ��Ϸ��õ��ġ�������ǣ��÷�Ҫ����ۿۡ�
    // �����ڲ��Իʱ����������������������������ϣ�����һ���õ���ϱ���
    // ֮��ֱ�� huigui ������ hjquit fail��������ǰ�������ǲ�����ϱ��� checking()��
    // ������ҿ��԰ѱ�������������һ���̶Ⱥ�һ�ι�����ȥ������߼�¼�͸�Ч�ʡ�
    // ������ⲻ��Ҳ�У���������ͳ��������˵���е����ˡ����Ǹĸİɡ� :)
    me->set_temp("this_time_mark", 1+random(9999) );
    // ��������Ϣ�Լ����ܣ����ں������á�
    // ����������ϣ�Ϊ��������Ϊ���ۣ��Ƚ���� move room��
    // �ٽ����ر���жϣ�������ʾ�ر���Ϣ������һ������Щ
    // �ر����Ϣ�Ͳ��ᱻ room �� long �����
    me->move(rooms);
    tell_object(me,"\n");
    // ���������ر�Ĵ���������˳���Ϸʱ�������˵ǼǵĻ�������
    // �ɹ���񣬶������ "last_skills" �Լ� "last_power" ��
    // ��ҿ���ѡ��Ʒ��Ŀ�����ܱ�������������������������ʹ����Щ���á�
    // ���ܱ������ƣ�ԭ�ȼ� 4/5�����80��������BUG���ƣ������ LV 0���������ü��ܡ�
    // �����������ƣ�ԭ���� 3/4��������� 30����� 5��
    // ���ڣ��Ȱ���һ�εļ�¼���͡�����������Ϸ�зǷ��˳�������
    // ���Ǽǳɼ����˳������ò���������ֻ��Խ��Խ�ͣ�ֱ����ȡ����
    // ���� last_power .
    if( me->query("huanjing2003/last_power") )
    {
        me->set("huanjing2003/last_power", me->query("huanjing2003/last_power") *3/4 );
        if( me->query("huanjing2003/last_power") > 30 )
            me->set("huanjing2003/last_power", 30);
    // ���̫�ͣ�������������� lv �޹ء�
        if( me->query("huanjing2003/last_power") < 6 )
            me->delete("huanjing2003/last_power");
    }
    // ���� last_skills .
    if( me->query("huanjing2003/last_skills_name")
      && mapp(me->query("huanjing2003/last_skills_name") )
      && sizeof( me->query("huanjing2003/last_skills_name") ) >= 1
      && me->query("huanjing2003/last_skills_lv")
      && mapp(me->query("huanjing2003/last_skills_lv") )
      && sizeof( me->query("huanjing2003/last_skills_name") ) >= 1 )
    {
        temp_map1 = me->query("huanjing2003/last_skills_lv");
        temp_map2 = ([]);

        key = keys( temp_map1 );
        // ����Ƿ��и����ֵ� skills. ����У��� skills ͨ�������Լ��봦���б��С�
        for( i=0; i<sizeof(key); i++ )
        {
            if( !undefinedp( me->query("huanjing2003/last_skills_name")[key[i]] ) )
            {
                temp_int = temp_map1[key[i]] *4/5;
                if( temp_int > 80 ) temp_int = 80;
                if( temp_int ) temp_map2 += ([ key[i] : temp_int ]);
                else me->delete( "huanjing2003/last_skills_name/"+key[i] );
            }
        }

        // ���ý��ͺ�ļ����б�
        me->set("huanjing2003/last_skills_lv", temp_map2 );
    }
    // ��ǰ�ߵ��ڶ���������һ��������������ǣ�����δ֪�ķǷ������
    else
    {
        me->delete("huanjing2003/last_skills_name");
        me->delete("huanjing2003/last_skills_lv");
    }
    // ok! ������д����жϣ�����������Чʹ�ô����������
    // ʹ����Щ��һ�εļ��ܼ�������
    // �������û�����ֵ��
    if( me->query("huanjing2003/last_power_times") )
    {
        if( !me->query("huanjing2003/last_power") )
        {
            tell_object(me, sprintf("�㻹����ʹ�� %d ���ۻ�������������������ۻ����������ܵõ��Ļ����������ͣ���δ��Ч��\n", me->query("huanjing2003/last_power_times") ));
            me->set_temp("hj_game_mepower", 5 );
        }
        else
        {
            me->add("huanjing2003/last_power_times", -1);
            tell_object(me, sprintf("��ʹ�����ۻ������Ľ������ý�����ʣ�� %d �Ρ�\n",
                me->query("huanjing2003/last_power_times") ) );
            me->set_temp("hj_game_mepower", me->query("huanjing2003/last_power") );
        }
    }
    else
        me->set_temp("hj_game_mepower",5 );
    // �Ƿ��м��ܱ�������
    if( me->query("huanjing2003/last_skills_times") )
    {
        if( !me->query("huanjing2003/last_skills_lv") )
        {
            tell_object(me, sprintf("�㻹����ʹ�� %d ���ۻ����ܣ�����������û���κ��ۻ����ܣ���δ��Ч��\n", me->query("huanjing2003/last_skills_times") ));
            me->set_temp("hj_game_skills/heal", "�ָ�֮��" );
            me->set_temp("hj_game_damages/heal", 3+random(8) );
        // Ĭ������Ϊֻ���� heal.
        }
        else
        {
            me->add("huanjing2003/last_skills_times", -1);
            tell_object(me,sprintf("��ʹ�����ۻ����ܵĽ������ý�����ʣ�� %d �Ρ�\n",
                me->query("huanjing2003/last_skills_times") ) );
            me->set_temp("hj_game_damages", me->query("huanjing2003/last_skills_lv") );
            me->set_temp("hj_game_skills", me->query("huanjing2003/last_skills_name"));
        }
    }
    // ��������Ĭ�ϼ��ܡ�
    else
    {
        me->set_temp("hj_game_skills/heal", "�ָ�֮��" );
        me->set_temp("hj_game_damages/heal", 3+random(8) );
    }
    if( 1 )
    {
        mapping find_name = ([
            "feng" : HIW"��֮����"NOR,
            "yu"   : HIM"��֮����"NOR,
            "lei"  : HIC"��֮����"NOR,
            "dian" : HIG"��֮����"NOR,
        ]);
        me->set_temp( "apply/short", ({ sprintf( "%s %s(%s)"NOR,
            find_name[ me->query_temp( "hj_game_find" ) ],
            me->query("name"), capitalize(me->query("id")) ), })
        );
        me->set_temp( "hj_apply_short", 1 );
    }
    // ���������Ϣ��ԭ���Ŀ����ۻ������Ϣ��������ȡ����
    me->set_temp("hj_hp_max", MAX_HP );
    // ������� lv �ӳ����á�
    temp_int = me->query("huanjing2003/lv_add");
    // �� lv 9 ʱ���������Զ�����Ϊ 20 ��
    me->add_temp("hj_game_mepower", temp_int/2 );
    me->add_temp("hj_hp_max", temp_int * 20 );
    // �� lv 9 ʱ����ϢΪ 700
    key = keys( me->query_temp("hj_game_damages") );
    for( i=0;i<sizeof(key);i++ )
        me->add_temp("hj_game_damages/"+ key[i], temp_int );
    // �� lv 9 ʱ�����ܿ��Զ�����Ϊ 50 ��

    // ȫ��������ϣ����ж��������������
    // ���˼�¼������������ң���һ���� max_hp ������
    if(me->query("huanjing2003/gift") )
    {
        tell_object(me,HIW"�����ǻþ���Ϸ��"+me->query("huanjing2003/gift")+"�ߣ�\n�㽫�õ����� 300 ����Ϸ�������Ϣ��������ǿ 10 ��Ľ�����\n"NOR);
        me->delete("huanjing2003/gift");
        me->add_temp("hj_hp_max", 300 );
        me->add_temp("hj_game_mepower", 10);
    }
    // ��֮������������Ч��  ��Ϣ��ǿ�������ǿ��������ǿ��
    if( me->query_temp( "hj_game_find" ) == "lei" )
        me->add_temp( "hj_hp_max", (me->query_temp( "hj_hp_max")/10) );
    if( me->query_temp("hj_hp_max") > 1500 )
        me->set_temp("hj_hp_max", 1500 );
    me->set_temp( "hjleave_usetimes", 0 );   // hjleave ָ������������ʱ�뿪ʱ������ɫ�İ�ȫ
    // ����������ϡ����� hp�����������Խ�����Ϸ�ˡ�
    me->set_temp("hj_hp",me->query_temp("hj_hp_max"));
    // �õ�һЩ����ĵ���
    // ������Ϸʱ����һ�� 120�� �������
    srl=new(__DIR__"shenren_ling");
    srl->waiting_delete( 120 );
    srl->move(me);
    tell_object(me,"��õ�һ"+srl->query("unit")+srl->query("name")+"��\n");

    // ������Ϸʱ����һ�� ����ˮ����( ����ʹ����ͬ���ı����� )
    srl=new(__DIR__"hj_obj_tools");
    srl->setme(2);
    srl->move(me);
    tell_object(me,"��õ�һ"+srl->query("unit")+srl->query("name")+"��\n");

    // ��һ������ˮ��
    srl=new(__DIR__"hj_obj_tools");
    srl->setme(0);
    srl->move(me);
    tell_object(me,"��õ�һ"+srl->query("unit")+srl->query("name")+"��\n");

/*  ��Ϊ�ؼ���Ʒ�����ٷ��š�
// ������Ϸʱ����һ�� �ع�֮����
    srl=new(__DIR__"hj_obj_tools");
    srl->setme(3);
    srl->move(me);
    tell_object(me,"��õ�һ��"+srl->query("name")+"��\n");
*/

    // ������� tianya �����飬����ǿ��ȡ����ҵ�����Ȩ��
    //    tell_object(me,HIB"����ؾ���һƬ�ž����ղŵ�����˿�����������ˡ�\n"NOR);
    //    if(!wizardp(me)) me->delete("channels");

    naihe = find_player("naihe");
    if(naihe && !naihe->query("env/no_hj_wizmsg") )
        tell_object( naihe, sprintf( HIR"�þ���Ϸ֪ͨ�κΣ�%s"HIR"(%s"HIR")����þ���Ϸ�� ( <set no_hj_wizmsg> ���ٷ��ͱ�����Ϣ)\n"NOR,
            me->query("name"), me->query("id") ));

    // add for yuchang.
    CHANNEL_D->do_channel( me, "rumor", sprintf( "��˵%s[%s]�����˻þ�����ʼ̽�ա�", me->query("name"), me->query("id") ));
    remove_call_out("checking");
    call_out("checking",1);
    remove_call_out("random_dispersion");
    call_out("random_dispersion",1);
    remove_call_out("robot_check");
    call_out("robot_check", 180 + random(420) );

    me->save();
    return;
}

void delete_me()
{
    message_vision("$N������ʧ�����ˡ�\n",this_object());
    destruct(this_object());
}

void real_random_dispersion()
{
    string random_rooms,msg;
    object obj,obj_me1,obj_me2,obj_me3,npc_ashman,rooms,me;
    int i;

    me=query("my_master");
    if (!me || me->query_temp("huanjing") != "start" || me->query_temp("hj_hp") < 1 )
        return;
    msg="��ȻһС�������ӹ����������ƺ�����һЩʲô��\n";
    // ���������뿪״̬���ǾͲ����ⷢ�Ŷ�����
    if( !present( "hj temp leave obj", me ) )
    {
        // ���� 1-3 �������Ʒ(��������NPC)��������䡣
        i = 1 + random(3);
        while( i-- )
        {
            random_rooms = HJ_DIR +"hj_room"+(1+random( HJ_ROOM_AMOUNT ));
            rooms = find_object(random_rooms);
            if(!rooms) rooms = load_object(random_rooms);
            obj=new( obj_list_all[random(sizeof(obj_list_all))] );
            obj->move(rooms);
            if(obj->query("msg")) msg=obj->query("msg");
            else msg="��ȻһС�������ӹ����������ƺ�����һЩʲô��\n";
            tell_room(random_rooms,msg);
        }
        random_rooms = HJ_DIR +"hj_room"+(1+random( HJ_ROOM_AMOUNT ));
        rooms = find_object(random_rooms);
        if(!rooms)
            rooms = load_object(random_rooms);
        // �����������򣬼�С���ˡ�
        // С����ͣ��ʱ������ˡ�
        i=1+random(2);
        while( i-- )
        {
            if( random(2) )
            {
                npc_ashman = new( __DIR__"hj_npc_ashman");
                npc_ashman->move(rooms);
                if(npc_ashman->query("msg")) msg=npc_ashman->query("msg");
                else msg="��ȻһС�������ӹ����������ƺ�����һЩʲô��\n";
                tell_room(random_rooms,msg);
            }
        }
        if( !random(5) )  // Ϊ����ڽ��գ����ᷢ�Ÿ����ɱ¾��NPC������Ϸ
        {
            npc_ashman=new(__DIR__"hj_npc_kill");
            npc_ashman->move(rooms);
            if(npc_ashman->query("msg")) msg=npc_ashman->query("msg");
            else msg="��ȻһС�������ӹ����������ƺ�����һЩʲô��\n";
            tell_room(random_rooms,msg);
        }
    }
    // �����뱾��ѡ���йص���Ʒ��������䡣
    if( about_me_obj == 0 )
    {
        about_me_obj=1;
        switch( this_object()->query("find_name") )
        {
            case "��֮����":
                obj_me1=new( obj_list_feng[0] );
                obj_me2=new( obj_list_feng[0] );
                obj_me3=new( obj_list_feng[1] );
                break;
            case "��֮����":
                obj_me1=new( obj_list_yu[0] );
                obj_me2=new( obj_list_yu[0] );
                obj_me3=new( obj_list_yu[1] );
                break;
            case "��֮����":
                obj_me1=new( obj_list_lei[0] );
                obj_me2=new( obj_list_lei[0] );
                obj_me3=new( obj_list_lei[1] );
                break;
            case "��֮����":
                obj_me1=new( obj_list_dian[0] );
                obj_me2=new( obj_list_dian[0] );
                obj_me3=new( obj_list_dian[1] );
                break;
        }

        // �⼸��Ĵ�������
        obj_me1->set("host_id",me->query("id"));
        obj_me1->setme(1);
        obj_me2->set("host_id",me->query("id"));
        obj_me2->setme(2);
        obj_me3->set("host_id",me->query("id"));  // ��ΪNPC����������Ҫ����Ʒ����

        random_rooms = HJ_DIR +"hj_room"+(1+random( HJ_ROOM_AMOUNT ));
        rooms = find_object(random_rooms);
        if(!rooms) rooms = load_object(random_rooms);
        obj_me1->move(rooms);
        if(obj_me1->query("msg")) msg=obj_me1->query("msg");
        else msg="��ȻһС�������ӹ����������ƺ�����һЩʲô��\n";
        tell_room(random_rooms,msg);

        random_rooms = HJ_DIR +"hj_room"+(1+random( HJ_ROOM_AMOUNT ));
        rooms = find_object(random_rooms);
        if(!rooms) rooms = load_object(random_rooms);
        obj_me2->move(rooms);
        if(obj_me2->query("msg")) msg=obj_me2->query("msg");
        else msg="��ȻһС�������ӹ����������ƺ�����һЩʲô��\n";
        tell_room(random_rooms,msg);

        random_rooms = HJ_DIR +"hj_room"+(1+random( HJ_ROOM_AMOUNT ));
        rooms = find_object(random_rooms);
        if(!rooms) rooms = load_object(random_rooms);
        obj_me3->move(rooms);
        if(obj_me3->query("msg")) msg=obj_me3->query("msg");
        else msg="��ȻһС�������ӹ����������ƺ�����һЩʲô��\n";
        tell_room(random_rooms,msg);
    }
}
// ���ϵ�����Ϸ��������
void random_dispersion()
{
    remove_call_out("random_dispersion");
    real_random_dispersion();
    call_out("random_dispersion", 60 + random(60) );
}
    
void real_robot_check()
{
    object checker, me;

    me=query("my_master");
    if (!me || me->query_temp("huanjing") != "start" || me->query_temp("hj_hp") < 1
      || !environment(me) || !environment(me)->query("room_mark")
      || !me->query_temp("this_time_mark")
      || present( "hj temp leave obj", me )   // ��ʱ�뿪��Ϸ�������� robot
    )
        return;
    checker = new( __DIR__"hj_robot_checker" );
    checker ->set("checking_player", me );
    checker ->set("this_time_mark", me->query_temp("this_time_mark") );
    checker ->move( environment(me) );
    checker ->start_check();
}
// robot ����������һ���ļ���ϡ�
void robot_check()
{
    remove_call_out("robot_check");
    real_robot_check();
    call_out("robot_check", 600 + random(600) );
}

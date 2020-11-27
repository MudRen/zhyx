// for hj_npc_quest.c  #include.
// naihe 16:30 03-10-19
// naihe 05-9-12 8:15 hj2003 ��������~~

void delete_me()
{
    int q_iii = query("iii"), award_score;
    object temp_obj,ob=this_object();

    if( q_iii == 0 || q_iii == 4 )
        message_vision("$N���¿��˿����Ҵ��뿪�ˡ�\n",ob);
    if( q_iii == 1 )
    {
        if(query("go_where") !="ok")
        {
            if(!query("following_name"))
                message_vision("$N������ã�����˿�ȥ�����ֶ���һ����ʧ��ͯ����\n",ob);
            else
            {
                message_vision("$N�����޵�����"+query("following_name")+"����˵����ȥ����ô���˶�ûȥ������\n",ob);
                message_vision("ֻ��$N���ĵ����Աߵ�·����ȥ�����ֶ���һ����ʧ��ͯ����\n",ob);
                temp_obj=find_player(query("following_id"));
                if(temp_obj && temp_obj->query_temp("huanjing") == "start" &&
                   temp_obj->query_temp("hj_score") > 200 )
                {
                    award_score = 30 + random(21);
                    temp_obj->add_temp("hj_score",-award_score );
                    tell_object(temp_obj,"������ã����������������Ӧ����һ����·��С������ʲô�ط��ģ�\n����������ӹ�һ˿�ھΡ�\n"HIR"��Ϸ��ʾ����ĵ÷ּ����� "+award_score+" �㡣\n"NOR);
                }
            }
        }
        else
        {
            message_vision("$N���˼��ˣ������˵������лл�㣬"+query("following_name")+"����\n",ob);
            message_vision("$N���˻��֣����˿�ȥ��\n",ob);
        }
    }
    if( q_iii == 2)
        message_vision("ֻ��$Nһ���Դ���˵��������ѽ�������˼����С�㻹ûι����\n$N����ææ���뿪�ˡ�\n",ob);
    if( q_iii == 3)
    {
        if(!query("asking") )
            message_vision("$N��̾һ����˵���������ˣ����ˣ����������ʹ���ȥ��\n",ob);
        else
        {
            if(query("asking") == "ok")
            {
                message_vision("ֻ��$N��������������벻��������ͷ���ң������˶�������ʿ����ô��Ϥ����\n",ob);
                message_vision("$Nһ��˵�ţ�һ���ⲽǰ�У��ʹ���ȥ�ˡ�\n",ob);
            }
            if(query("asking") == "fail")
            {
                message_vision("$Nҡͷ̾�������ѵ�����û���ˣ��ܹ���������֮������֪���ģ���˵�գ������ʹ���ȥ��\n",ob);
            }
            if(query("asking") == "waiting" && query("asking_for_id") )
            {
                temp_obj = present(query("asking_for_id"),environment(ob));
                if(temp_obj)
                {
                    message_vision("$N��̾һ����˵������"+query("asking_for_name")
                        +"������δ��õ���������"+query("the_answer")+"����\n",ob);
                    message_vision("$Nʮ��ʧ����˵��������������������㾹Ȼ��֪��������ϸ����ɣ���\n",ob);
                    message_vision("$N����֮ɫ������������ʱ�����˳�˼�С�\n",temp_obj);
                    temp_obj->start_busy(20);
                    message_vision("ֻ��$Nһ��ҡ��ͷ��һ���뿪�ˡ�\n",ob);
                }
                else
                {
                    temp_obj=find_player(query("asking_for_id"));
                    if( temp_obj && temp_obj->query_temp("huanjing") =="start" )
                    {
                        ob->move(environment(temp_obj));
                        message_vision("ֻ��һ���������˹���������$N��ͷ�������"
                            +"�����������������֮�ˣ���Ӧ�ش��ҵ����⣬ȴ�������ߣ���\n",temp_obj);
                        message_vision("���˺���һ����$N������$N�������ã�һ����ľ"
                            +"��֮��������ʱ�������ã�\n",temp_obj);
                        temp_obj->start_busy(30);
                        message_vision("$N˵����������Һú÷�ʡ��ʡ�գ����԰վ�Ȼ�ʹ���ȥ��\n",ob);
                    }
                }
            }
        }
    }
    if( q_iii == 5 || q_iii == 6 )
    {
        if( query("all_found") )
            message_vision("$Nһ��ϲ��֮�飬���Ա����˿�ȥ��\n", ob);
        else
            message_vision("$N��̾һ�������Ա����˿�ȥ��\n", ob);
    }
    destruct(ob);
}

void init()
{
    switch( query("iii") )
    {
        case 0: case 4:
            add_action("do_gmai",({ "gmai", "gbuy" }) );
            add_action("do_glist","glist");
            break;
        case 1: case 7:
            // ��� set �������Ҫ���������
            if( !query("go_where") )
                set("go_where", 2 + random( HJ_ROOM_AMOUNT -1 ) );
            add_action("do_answer","answer");
            break;
        case 2:
            add_action("do_lianli","lianli");
            break;
        case 3:
            add_action("do_huida","huida");
            break;
        case 5: case 6:
            add_action("do_found", "found" );
            add_action("do_foundall", "foundall" );
            break;
    }
}

int ask_help()
{
    switch(query("iii"))
    {
        case 0: case 4:
            command("hehe "+query("id"));
            command("say ����������һЩ����������(gmai)����Ҳ�����ȿ����۸��(glist)����");
            break;
        case 1:
            if(!query("following_name"))
            {
                command("say ������·�˰������и��ط�������"+chinese_number(query("go_where"))
                    +"���ģ����ܴ���ȥ������(answer ok)��");
                remove_call_out("delete_me");
                call_out("delete_me",60);
            }
            else
                command("say ������·�ˣ�"+query("following_name")+"Ҫ����ȥ�ҡ�"
                    +chinese_number(query("go_where"))+"���ء���");
            break;
        case 2:
            command("say ��Ŷ��������������������һȭ�����ҿ�����������ж����˵�ɣ���");
            command("say �������£���С�޶����˲����ң��������׼����������(lianli)�أ���");
            break;
        case 3:
            if( !query("asking_for_id") )
            {
                command("say ����������ɽ��������������Ӣ�۶��֣�ȴ��֪��˭���ã���");
                command("say ������֪������Ը��ش��ҵ�����(huida ��)����");
            }
            else
                command("say ����������������Ӣ�ۺú���������ε�����֪����");
            break;
        case 5:
            if( query("found_sword") != "yes" )
            {
                command("say ������˵��һ��"+query("finding_name")+"�������࣬�˵��Ƿ����쳣�����뿴һ������");
                command("say ��������ܰ����ҵ�(found ����id)��������Һ��𣿡�");
            }
            if( query("found_all_sword") != "yes" )
                command("say ���������Ѽ�һ�ױ��������ܰ����ҵ��Ļ�(foundall)��������Һ��𣿡�");
            if( query("all_found") )
                command("haha");
            break;
        case 6:
        if( query("found_crystal") != "yes" )
        {
            command("say ������˵��һ��"+query("finding_name")+"����Ī�������뿴һ������");
            command("say ��������ܰ����ҵ�(found ˮ����id)��������Һ��𣿡�");
        }
        if( query("found_all_crystal") != "yes" )
            command("say ���������Ѽ�һ��ħ��ˮ�������ܰ����ҵ��Ļ�(foundall)��������Һ��𣿡�");
        if( query("all_found") )
            command("haha");
            break;
    }
    return 1;
}

int do_found( string arg )
{
    object me = this_player(), ob = this_object(), f_obj;
    string f_name;
    int award_score;

    if( !me_ok(me) ) return 0;
    if(me->is_busy() || me->query_temp("hj_need_waitting") )
        return notify_fail("�㻹æ���أ��п��˲Ű��˰ɡ�\n");

    if( !arg ) return notify_fail("���ҵ���ʲô��\n");
    f_obj = present( arg , me );
    if( !f_obj ) return notify_fail("������û������������\n");

    message_vision(CYN"$N"NOR+CYN"�˷ܵ��ó�һ"+f_obj->query("unit")+f_obj->name(1)+NOR+CYN"������$n"NOR+CYN"˵���������ǲ��������������\n", me, ob );

    if( query("found_sword") == "yes" || query("found_crystal") == "yes" )
    {
        command("haha");
        command("say �������Ѿ���ʶ��"+query("finding_name")+"�ˣ����ͷ����ˡ���");
        return 1;
    }

    f_name = query("finding_name");

    if( !f_obj->query("cj-sheng.zb-ke") || f_obj->query("cj-sheng.zb-ke") != ob
        || delcolor( f_obj->name(1) ) != f_name )
    {
        command("shake");
        command("say ���ⲻ����Ҫ�ҵ�"+f_name+"����");
        return 1;
    }

    // ��ȷ�ˣ�
    f_obj->move( ob );
    command("ah");
    command("touch "+me->query("id"));
    command("say ���ԣ��������Ҫ�ҵ�"+f_name+"������̫��л���ˣ���");
    message_vision( sprintf( CYN"$N"NOR+CYN"��%s"NOR+CYN"���˹�ȥ���������ã�̾��������%s"NOR+CYN"���ܵ�һ�������޺��ӣ���\n", f_name, f_name ), ob );
    message_vision( CYN"$n"NOR+CYN"��$N"NOR+CYN"˵��������ν������Ӣ�ۣ���"+f_name+NOR+CYN"���Ǹ��������У���\n$n"NOR+CYN"˵�꣬��"+f_name+NOR+CYN"�ֽ�����$N"NOR+CYN"���С�\n"NOR, me, ob);

    // ��������Ҫ���ܹ��õ��������߽���
    f_obj->set("power", f_obj->query("power") * 2 );
    if( f_obj->query("power") > 50 )
        f_obj->set("power", 50 );
    f_obj->set("use_times", f_obj->query("use_times") * 2 );
    if( f_obj->query("use_times") > 20 )
        f_obj->set("use_times", 20);

    award_score = 30 + random(21);
    f_obj->move( me );
    message_vision(CYN"$N"NOR+CYN"ֻ����$n"NOR+CYN"���ֳ��飬�Ѳ���ԭ�ȵĸо���\n"NOR, me, f_obj);
    write(HIR"��Ϸ��ʾ����ĵ÷������� "+award_score+" �㣡\n"NOR);
    me->add_temp("hj_score", award_score );

    set( "found_sword", "yes" );
    set( "found_crystal", "yes" );

    if( query("found_all_sword") == "yes" || query("found_all_crystal") == "yes" )
    {
        set("all_found", 1);
        remove_call_out("delete_me");
        call_out("delete_me", 3 );
    }

    return 1;
}

int do_foundall()
{
    object me = this_player(), ob = this_object(), *temp_obj_list, temp_obj;
    string *found_list_id, msg, to_say;
    int i, award_score;

    if( !me_ok(me) ) return 0;
    if(me->is_busy() || me->query_temp("hj_need_waitting") )
        return notify_fail("�㻹æ���أ��п��˲Ű��˰ɡ�\n");

    if( query("iii") == 5 )
    {
        msg = "��";
        found_list_id = ({ "qt jian", "lq jian", "by jian", "bs jian",
            "yd jian", "hj jian", "nl jian", "xy jian", "dh jian", });
    }
    else
    {
        msg = "ˮ��";
        found_list_id = ({ "kf sj", "by sj", "ll sj", "yd sj",
                "gs sj", "fh sj","dh sj", });
    }

    message_vision(CYN"$N"NOR+CYN"����$n"NOR+CYN"�˷ܵ�˵��������������һ��"+msg+"�ˣ���\n"NOR, me, ob );

    if( query("found_all_sword") == "yes" || query("found_all_crystal") == "yes" )
    {
        command("haha");
        command("say �������Ѿ�������һ��"+msg+"�����ͷ����ˡ���");
        return 1;
    }

    // �жϿ�ʼ
    command( "oh2" );
    command( "say ���죬���ҿ�������" );
    to_say = CYN"$N"NOR+CYN"ϸϸ���������ҿ�������";

    temp_obj_list = ({ });
    for( i=0; i<sizeof(found_list_id); i++ )
    {
        temp_obj = present( found_list_id[i] , me );
        if( !temp_obj ) break;
        if( i == 0 )
            to_say += temp_obj->name(1) + NOR+CYN;
        else to_say += "��"+ temp_obj->name(1) + NOR+CYN;
        temp_obj_list += ({ temp_obj });
    }
    to_say += "������\n"NOR;

    message_vision( to_say, ob );
    if( sizeof( temp_obj_list ) != sizeof( found_list_id ) )
    {
        command( "shake" );
        command( "say �������������ƺ�������ȫ������");
        return 1;
    }

    // ������ :)
    // �����������
    for( i = 0; i<sizeof( temp_obj_list ); i++ )
        destruct( temp_obj_list[i] );

    command("touch "+me->query("id") );
    command("say ���ԣ��ԣ�������Щ"+msg+"��̫���ˣ����������������ˣ���");
    command("say ������Ϊ����������ҵ�һ������ɣ���");
    message_vision( CYN"$n"NOR+CYN"�ӹ�����һ��"+msg+"������������$N"NOR+CYN"��ǰһ�Ρ�\n"NOR, me, ob);

    if( query("iii") == 5 )
        award_score = 400 + random(101);
    else award_score = 300 + random(101);
    me->add_temp("hj_score", award_score );
    write(HIR"��Ϸ��ʾ����ĵ÷������� "+award_score+" �㣡\n");

    set( "found_all_sword", "yes" );
    set( "found_all_crystal", "yes" );

    if( query("found_sword") == "yes" || query("found_crystal") == "yes" )
    {
        set("all_found", 1);
        remove_call_out("delete_me");
        call_out("delete_me", 3 );
    }

    return 1;
}


// �ش�ʧ���ߣ�æʱ 10 ��  δ���ü��ش��ߣ��������˵أ�æʱ 20 ��
// ���Ѳ����ټ�����������֮��ģ����سͣ�æʱ 30 �롣
int do_huida(string arg)
{
    object qxd,me=this_player();
    mapping data1,data2,data3,data4;
    string qt_name1,qt_name2,qt_name3,qt_name4,*qt_type,temp_type;
    int i,qt_temp1,qt_temp2,qt_temp3,qt_temp4, score_is;

    if( !me_ok(me) ) return 0;

    qxd = present("qixing deng",me);
    if(!qxd) return 0;

    if(!qxd->query("hj_quest_info1") || !qxd->query("hj_quest_info2") ||
       !qxd->query("hj_quest_info3") || !qxd->query("hj_quest_info4") )
        return 0;

    if(me->is_busy() || me->query_temp("hj_need_waitting") )
        return notify_fail("�㻹æ���أ����е����ٽ������ʰɡ�\n");

    if(query("asking_for_id") && me->query("id") != query("asking_for_id") )
        return notify_fail(query("name")+"�Ѿ�������"+query("asking_for_name")+"�ˣ����ǲ�Ҫ���ŵĺá�\n");

    if(!arg) return notify_fail("��Ҫ�ش�ʲô��\n");

    if(!query("asking_for_id"))
    {
        if(arg!="��") return notify_fail("����Ը��������ʣ��ͻش𡰺á��ɣ�\n");

    // ������ڱ�����Ϸ��Ѱ�5��Ԥ������ⶼ��Թ��ˣ������ٷ������⡣
        message_vision("$N����˵�������ðɣ���;������ң�����֪��֪������\n",me);
        if(sizeof( me->query_temp("hj_quest_answer") ) >=5 )
        {
            command("say ������֪����֮�����࣬��������֮�¡������������㣿��");
            command("smile");
            return 1;
        }

        remove_call_out("delete_me");
        set("asking_for_id",me->query("id"));
        set("asking_for_name",me->query("name"));
        set("asking","waiting");
        set("cannot_rdmove","yes");

        data1 = qxd->query("hj_quest_info1");
        data2 = qxd->query("hj_quest_info2");
        data3 = qxd->query("hj_quest_info3");
        data4 = qxd->query("hj_quest_info4");

        // ���濪ʼ��ȡ��������
        
        qt_type = ({ "int","str","con","dex","balance" });
        // ����  ����  ����  ��  ���
        temp_type = qt_type[random(sizeof(qt_type))];
        // ��ֹ����ڱ�����Ϸ���ظ��ش�����
        for(i=0;i<sizeof(qt_type);i++)
        {
            if(me->query_temp("hj_quest_answer/"+temp_type) == "ok")
                temp_type = qt_type[i];
            else break;
        }
        set("quest_type",temp_type);

        qt_name1 = data1["name"];
        qt_name2 = data2["name"];
        qt_name3 = data3["name"];
        qt_name4 = data4["name"];
        qt_temp1 = data1[temp_type];
        qt_temp2 = data2[temp_type];
        qt_temp3 = data3[temp_type];
        qt_temp4 = data4[temp_type];

        // �����Ҳ�֪��LPC�Ƿ��� max �ĺ�����ֻ���Լ�д���Һò�̫������
        if( qt_temp1>=qt_temp2 && qt_temp1>=qt_temp3 && qt_temp1>=qt_temp4 )
            set("the_answer",qt_name1);
        if( qt_temp2>=qt_temp1 && qt_temp2>=qt_temp3 && qt_temp2>=qt_temp4 )
            set("the_answer",qt_name2);
        if( qt_temp3>=qt_temp1 && qt_temp3>=qt_temp2 && qt_temp3>=qt_temp4 )
            set("the_answer",qt_name3);
        if( !query("the_answer") )
            set("the_answer",qt_name4);
        // ����ȥ����ɫ�ľ��ӣ���ֹСBUG
        set("the_answer", delcolor( query("the_answer") ) );
        // �ڲ�����OK���������ȥ�����°� :)
        command("nod");
        command("say �����Ƿ������⼸���ˣ������� "+qt_name1+"��"+qt_name2+"��"+qt_name3+"��"+qt_name4+" ����");
        switch(temp_type)
        {
            case "int":
            command("say ��������һ�ˣ�����֮����ߣ���˹���һ�����������Ը��\n          �ɾʹ��¡����֮�ˣ�����Ӣ�ۣ���");
            break;
            case "str":
            command("say ����νӢ�����ͣ����������޲���֮��֮�ˣ�������һ�ˣ�\n          �������������ʯ��ɽ��Ҳ�����Ӣ�۶��֣���");
            break;
            case "con":
            command("say �����Ե����Եÿ��п࣬��Ϊ�����ˡ�������һ�ˣ���������\n          ���ˣ�Ҳ�ǹǸ��档���֮�ˣ��γ�ɴ��£����кβ��ܳ�֮Ӣ�ۣ���");
            break;
            case "dex":
            command("say ���Թ�Ӣ�۽Ժú�����������ȴ��һλ��ȴ�������ռ���������\n          �츳��ߣ��Ṧ���ˣ��մ���һƬ��أ����֮�ˣ�Ҳ�ÿɳ�Ӣ�ۣ���");
            break;
            case "balance":
            command("say �������ƣ�һ���ѵ�Ӣ�ۺ���������һλ�������ķ���������ѣ�\n          ���޹������գ�������β��ܳ�֮Ӣ�ۣ���");
            break;
        }
        command("say ������֪���������֣��ͻش�(huida)���Ұգ���");
        message_vision("$N��������һʱ���ס�ˣ���������Ӧ��һ�㡣\n",me);
        write(HIR"��Ϸ��ʾ����ֻ��60���ʱ�䣡���ش�\n"NOR);
        remove_call_out("delete_me");
        call_out("delete_me",61);
        return 1;
    }
    // ����ǿ��ȥ������Ŀո�����
    arg = replace_string( arg, " ", "" );
    arg = replace_string( arg, "��", "" ); // ��ȫ�Ƿ��ŵġ��հס�Ҳȥ����
    message_vision("$N�����룬˵�������������"+arg+"����\n",me);
    // �ش����
    if( arg != query("the_answer") )
    {
        set("asking","fail");
        remove_call_out("delete_me");
        command("sure "+me->query("id"));
        command("say ����˵�ò��ԡ�������ģ�����������"+query("the_answer")+"����");
        message_vision("$Nʮ��ʧ����˵��������������������㾹Ȼ��֪��������ϸ����ɣ���\n",this_object());
        message_vision("$N����֮ɫ������������ʱ�����˳�˼�С�\n",me);
        me->start_busy(10);
        set("asking_for_id","no");
        call_out("delete_me",1);
        return 1;
    }
    // �ش���ȷ����ҵõ���������������ֵ��������Ϸ�������������ˣ���������������⡣
    remove_call_out("delete_me");
    message_vision("$N���������ӣ�˵�����������벻����Ҳ��֪���������֣���\n",this_object());
    command("say ������֪���֮�㣬����һ���������㡣��");
    message_vision("����˵�꣬ȴ�����ó�Щʲô����ֻ��ͻ�ذ�����$N����һ�ģ�\n",me);
    message_vision("$Nֻ���ù���Ī����ȴ�ƺ��־�����Щʲô�仯����\n",me);
    me->set_temp("hj_quest_answer/"+query("quest_type"),"ok");
    if(me->query_temp("hj_score"))
    {
        score_is = 200 + random(101); // ��߿ɻ� 300 �㽱��
        me->add_temp("hj_score", score_is );
        write(HIR"��Ϸ��ʾ�������Ϸ�÷������� "+score_is+" �㣡\n"NOR);
    }
    set("asking","ok");
    call_out("delete_me",1);
    return 1;
}

// naihe 05-9-12 8:06 �޸ģ�lianli �ɹ�ʱ��æʱ��
int do_lianli()
{
    object me=this_player();
    string id=me->query("id");
    int temp,power=me->query_temp("hj_game_mepower");

    if( !me_ok(me) ) return 0;

    if(!power) return 0;

    if(me->is_busy() || me->query_temp("hj_need_waiting"))
        return notify_fail("�㻹æ���أ����ǵȿ����ˣ�ר�ĵ��������ɣ�\n");

    if(me->query_temp("hj_hp") < power *2 )
        return notify_fail("�����Ϣ̫�����޷�ʹ�����ˣ������������\n");

    if(query("last_id") && query("last_id") == id )
    {
        command("say ����ѽ�����Ѿ��̹����ˣ�����ô��ô�ޱ��ģ���");
        return 1;
    }
    message_vision("$N���һ����ʹ������"+query("name")+"�����һȭ��\n",me);
    if( !random(3) )
    {
        me->start_busy(3+random(3));
        message_vision("ֻ��$N�þ�ȫ����ȴ�ƴ���ͭǽ����֮�ϣ�$N��ʱ��ʹ�쳣���о����ƶ����ֱ�һ�㣡\n",me);
        me->add_temp("hj_hp", -power);
        message_vision(query("name")+"���Ǻǡ�Ц��Ц��������$N��ͷ˵�������޶������������ġ���\n",me);
        this_object()->add("use_times",-1);
        if(query("use_times") <=0 )
        {
            remove_call_out("delete_me");
            call_out("delete_me",1);
        }
        return 1;

    }
    me->start_busy(1); // �����ɹ�ʱֻ��1��æʱ��
    set("last_id",id);
    if(power<15)
    {
        message_vision("ֻ��"+query("name")+"����û֪����ȫ�������ˣ�\n",me);
        command("pat "+id);
        command("say ���޶��������а������������̽��㣬Ҫ��������Ŷԡ�����");
        temp=3+random(3);
    }
    else if(power<30)
    {
        message_vision("ֻ���á��ء���һ����"+query("name")+"��������ȭ����ȴֻ��΢΢һ��\n",me);
        command("nod");
        command("say ���޶����е��������������õò�̫�ԣ������̽���ɡ�����");
        temp=2+random(2);
    }
    else if(power<50)
    {
        message_vision("ֻ����һ�����죬"+query("name")+"��������ȭ����ʱ��������һ����\n",me);
        command("consider");
        command("say ���޶���������С�ۣ������⻹�ܴ�ø��ã������������������㡭����");
        temp=1+random(2);
    }
    else
    {
        message_vision("ֻ����"+query("name")+"�ƺ�һ��������ȭ����ʱ�������˺ü�����\n",me);
        command("thumb "+id);
        command("say ���޶��������ܲ����ۣ���ͷ���Ҹ����������һ��Ҫ��ɣ�������");
        temp=1;
    }
    command("whisper "+id+" ����������������������������ô��");
    message_vision("$N����é���ٿ�����ʱ���������ƺ����ͼ�Ӱ����������࣡\n",me);
    me->add_temp("hj_game_mepower",temp);
    this_object()->add("use_times",-1);
    if(query("use_times") <=0 )
    {
        remove_call_out("delete_me");
        call_out("delete_me",1);
    }
    return 1;
}

int do_answer(string arg)
{
    object me = this_player();
    int award_score;

    if( !me_ok(me) ) return 0;

    if(!arg || (arg!="ok" && arg!="byebye" && arg!="here?"))
        return notify_fail("�ش�ʲô����Ӧ(ok)���Ƿ���(byebye)�������ҵ��˵ط���(here?)��\n");

    if(arg == "ok")
    {
        if(query("following_name"))
        {
            if(me->query("id") == query("following_id"))
                write("��˵��Ҫ����ȥ�˵ġ�\n");
            else command("say ��"+query("following_name")+"˵��Ҫ����ȥ��ѽ����");
            return 1;
        }
        else
        {
            if(query("last_follow") == me->query("id"))
                return notify_fail("�ղ��㲻��Ҳ˵����ƭС���ӣ���Ҫ������\n");

            set("following_name",me->query("name"));
            set("following_id",me->query("id"));
            set("cannot_rdmove","yes");
            message_vision("$N����"+query("name")+"����˵�������Ҵ���ȥ�ɣ���\n",me);
            command("nod2 "+me->query("id"));
            command("say ����Ҫȥ���ǡ�"+chinese_number(query("go_where"))+"��������");
            command("say ��������˾͸�����(answer here?)�����Ǻܸ�л�㰡����");
            remove_call_out("delete_me");
            call_out("delete_me",180); // �������ܼ�����3�����й������
            command("follow "+me->query("id"));
            return 1;
        }
    }

    if(arg == "byebye")
    {
        if(!query("following_id")) return notify_fail("��û��Ӧ���أ���˵�ݰݣ�\n");
        if(me->query("id") != query("following_id") )
            return notify_fail("�ֲ������Ӧ����ȥ�ģ��㰮�߱���ô��\n");

        message_vision("$N�������Դ�������"+query("name")+"˵�������Ҵ�������ȥ�ˣ��������ɣ������ˡ���\n",me);
        delete("following_name");
        delete("following_id");
        command(":( "+me->query("id"));
        set("last_follow",me->query("id"));
        command("follow none");
        award_score = 5 + random(6);
        me->add_temp("hj_score", -award_score );
        if( me->query_temp( "hj_score" ) < 0 )
            me->set_temp( "hj_score", 0 );
        // ������Ӧ�����飬��������Ϸ�÷֡������⻹���Ǻõģ�������ȷ��ʾ���������������10��ĵ÷֣�
        // ���ǰ�;�����ˡ�������֮��ģ���ô��ʱ�޵���֮�󣬽��������50��ĵ÷֡�
        write("������е�һ˿�ھΣ�\n"HIR"��Ϸ��ʾ����ĵ÷ּ����� "+award_score+" �㡣\n"NOR);
        delete("cannot_rdmove");
        remove_call_out("random_move");
        call_out("random_move",1);
        remove_call_out("delete_me");
        add("use_times",-1);
        if(query("use_times") < 1)
            call_out("delete_me",1);
        else call_out("delete_me",30+random(31));
        return 1;
    }
    if(arg == "here?")
    {
        if(!query("following_id") || query("following_id") !=me->query("id") || !query("go_where") )
            return 0;
        if(environment( this_player() )->query("room_mark") != query("go_where") )
            return notify_fail(query("name")+"ҡ��ҡͷ��˵���������������ﰡ����\n");

        message_vision("$N��"+query("name")+"�ʵ��������ǲ���Ҫ�������\n",me);
        command("jump");
        command("say ���ǰ�����ĺ�лл�㣡��");
        set("go_where","ok");
        award_score = 50 + random(31);
        // ��߿ɻ�� 80 �ֵĽ������ܲ�������
        write("������˱��ˣ�������켫�ˡ�\n"HIR"��Ϸ��ʾ����ĵ÷������� "+award_score+" �㣡\n"NOR);
        me->add_temp("hj_score", award_score );
        remove_call_out("delete_me");        
        call_out("delete_me",1);
        return 1;
    }
    return 1;
}


// naihe 05-9-12 8:09 glist ʱΪʲôҪ cmd(say) ? ������Ե�޹ʾͱ� flood �����ơ�
int do_glist()
{
    object me=this_player();
    int i,iii;
    string *lists,*for_debug,go_on="no";

    if( !me_ok(me) ) return 0;
    lists = keys(list_temp);
    for_debug= keys(all_values);
    write("----[ �������¹�"+chinese_number(sizeof(lists))+"�� "+HIG+query("sell_this_time")+NOR+" ��Ʒ���ۣ�]----\n\n");

    // �Ѿ��Ļ�����ѧ���ã�֮ǰʲô��ӳ���Ҷ���������
    // д�˸����˸����ƺ��Ƚϴ�֮�⣬��������Ϊ�����ķ�ֹbug�ж�����
    // yeah ���²����ˣ�obj_copy.h ���ӳ������ҸĶ�û���⣡������
    // 8:29 02-10-30 
    for(i=0;i< sizeof(lists);i++)
    {
        for(iii=0;iii<sizeof(for_debug);iii++)
        {
            go_on="no";
            if(lists[i] != for_debug[iii]) continue;
            go_on="yes";
            break;
        }
        if(go_on == "yes")
            printf("%-10s( %-4s )     �۸� %-30d\n",list_temp[lists[i]],lists[i],all_values[lists[i]]);
    }
    // ����� ���� ����Ū�������ǺǺ� ̫������Ϊ�� (%-4)s �ģ�Ū����Ū���ã� papaya
    write("\n----[ ����Ϸ���ֹ����Ʒ��������Ҫһ����ʯ������һ��  ָ�gmai ��Ʒid ]----\n");
    return 1;
}

// naihe 05-9-12 8:15 gmai ʱż����NPC���޶˶ˡ��� say ��һ�仰�������˹���ʱ����ң����˻�е��Ի��~~
int do_gmai(string arg)
{
    object money,gem,goods,me=this_player();  // goods  n.��Ʒ;����
    string goods_name,have_gem="yes";
    int temp_set,temp_value;

    if( !me_ok(me) ) return 0;

    if( query("use_times") <= 0) return 0;

    if(!arg) return notify_fail("��Ҫ��ʲô������\n");


    if(sscanf(arg, "%s ok", goods_name) )
        have_gem="no";
    else goods_name = arg;

    if(have_gem == "yes")
    {
        gem = present("red baoshi",me);
        if(!gem) gem = present("blue baoshi",me);
        if(!gem) gem = present("green baoshi",me);
        if(!gem)
        {
            return notify_fail( "��û�б�ʯ�������ȷʵҪ�򣬼�Ǯ�ɵüӱ��� <gmai ��Ʒid ok>\n");
            return 1;
        }
    }

    if(!list_temp[goods_name] || !all_dir[goods_name] ||
       !all_set[goods_name] || !all_values[goods_name] )
        return notify_fail("û�������������\n");

    temp_value = all_values[goods_name];
    if(have_gem == "no") temp_value += temp_value;
    if(!me->query_temp("hj_score") || me->query_temp("hj_score") <= temp_value)
        return notify_fail("��û���㹻����Ϸ�÷֣����ܹ���������\n");
    goods=new(__DIR__+all_dir[goods_name]);
    if( all_set[goods_name] == 111) temp_set = 0;
    else temp_set = all_set[goods_name];
    goods->setme( temp_set );
    goods->move(me);
    me->add_temp("hj_score", -temp_value);
    if(have_gem == "yes")
    {
        message_vision(sprintf("$N�ͳ�һ%s%s����%s������һ%s%s��\n",
            gem->query("unit"),gem->query("name"),query("name"),
            goods->query("unit"),goods->query("name")),
            me
        );
        destruct(gem);
    }
    else
    {
        message_vision(sprintf("$N��%s������һ%s%s��\n",
            query("name"),goods->query("unit"),goods->query("name")),
            me
        );
    }
    this_object()->add("use_times",-1);
    if(query("use_times") <=0 )
    {
        remove_call_out("delete_me");
        call_out("delete_me",1);
    }
    return 1;
}

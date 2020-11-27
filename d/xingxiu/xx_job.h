// Code of ShenZhou
void dest_bug(object bug);
void setup_npc(object me, object ob);

void init()
{
        add_action("do_search", "search");
	add_action("do_search", "zhao");
}	

int do_search(string arg) {
		

	string* n= ({
		"/d/xingxiu/forest10",
        	"/d/xingxiu/forest2",
        	"/d/xingxiu/forest3",
        	"/d/xingxiu/forest11",
        	"/d/xingxiu/forest4",
        	"/d/xingxiu/forest5",
        	"/d/xingxiu/forest1",
        	"/d/xingxiu/forest12",
        	"/d/xingxiu/forest6",
        	"/d/xingxiu/forest7",
        	"/d/xingxiu/forest8",
        	"/d/xingxiu/forest9",
        });

	object bug, me, fighter, room, gold, ob;

	int kar1, kar2, kar3, pot, max_pot, damage, find;	

	me=this_player();

	if( !arg || arg=="" ) return 0;
	
	if( arg=="bug" || arg=="chong"){

		if (!present("wa guan", me))
                        return notify_fail("���ҵ�������ʲô��ʢ�أ�\n\n");
                        
                if (me->query("jingli")<me->query("max_jingli")/5)
                        return notify_fail("������Ϣһ�°ɡ�\n\n");
                        
		if (me->is_busy()) return
                        notify_fail("����һ��������û����ɡ�\n"); 
                        
		if (me->is_fighting()) return
                        notify_fail("���Ȱɵ�����������˵�ɡ�:)\n");
                        
		if (me->query_temp("found")==1) return
                        notify_fail("������Ȼ�ȥ�������������ɵȼ��ˡ�\n");
                                       
                //if (me->query_temp("bug_out")==1)
                //        return notify_fail("�����Ѿ������ˣ��Ͽ�ץ�ɣ�\n");
                
                if (me->query_temp("xx_job")!=1)
                        return notify_fail("������ʲô�ã�\n");
                
		me->add("jingli",-10);
		me->add("jing",-10);
		me->start_busy(random(1)+1);
		
		me->add("find_bug",1);
		me->add_temp("xx/find",1);

                message_vision("$N�������������ֽ���֦��Ҷ��������ϸѰ�Ҷ�����ټ���\n",me);
		
		kar2=(me->query("int")+me->query("con")+me->query("str"))*(random(2)+1);
		kar1=me->query("kar");		

		if (me->query("find_bug")>random(20)) {
			me->set("find_bug",0);
                                
			room = load_object(n[random(sizeof(n))]);
                        
                        message_vision("$N�������ң�����û��˿��������ټ���ֻ���뿪�������ĵط�Ѱ�ҡ�\n",me);
			message_vision("$N����ææ���뿪�ˡ�\n",me);
			me->move(room);
			message_vision("$N���˹�����\n",me);			
			return 1;
		}
		
		kar3=random(kar1*3);
		find=me->query_temp("xx/find");
		
		if (wizardp(me)) {
				printf("my kar=%d  kar=%d  randkar=%d  time: %d\n", kar1, kar3, kar2, find);
		}
		
		if ((kar3>kar2 && find>10) || (find>=30)) {

                        message_vision(HIG"ͻȻ��һֻС�������˳�����Ѹ�ٵ������š�\n"NOR, me);
                        bug=new("/d/xingxiu/npc/duchong");
			bug->move(environment(me));
			bug->set("playerid",me->query("id"));
                        me->set_temp("bug_out",1);
			me->set_temp("xx/find", 0);
			
			if (wizardp(me)) {
				printf("player id: %s \n", bug->query("playerid"));
			}
						
			return 1;
			
 		}
		
                   if (random(50)<=3 && (me->query("combat_exp")>=150000) && me->query_temp("xx_job")) { 

                        message_vision(HIR"ͻȻ�������Խ��һ���ˣ��ߺ�һ���������޼��ˣ�����������\n"NOR,me);
                     fighter = new(CLASS_D("generate") + "/xxnpc.c");
                     NPC_D->set_from_me(fighter, me, 110 + random(20));
                     fighter->add_temp("apply/attack", fighter->query_skill("force") *
					     1/ 15);
                     fighter->add_temp("apply/dodge", fighter->query_skill("force") *
					     1/ 15);
                     fighter->add_temp("apply/parry", fighter->query_skill("force") *
					     1/ 15);
                     fighter->add_temp("apply/damage", 5 + 1 * 7);
                     fighter->add_temp("apply/unarmed_damage", 5 + 1 * 7);
                     fighter->add_temp("apply/armor", 10 + 1 * 15);
			fighter->set("player",me->query("id"));
			fighter->move(environment(me));
			fighter->kill_ob(me);
			//fighter->set_busy(random(2));			
			return 1;
		}
		
		
		if (random(kar1*3)<1){
			message_vision(HIW"$N��ǰ����һ�����ۣ����ӣ�\n"NOR,me);
			gold=new("/clone/money/silver");
			gold->move(environment(me));
			return 1;
		}
		
		if (random(kar1*2)<1){
			message_vision(YEL"$N��ǰͭ��һ�����ۣ�ͭǮ :(\n"NOR,me);
			gold=new("/clone/money/coin");
			gold->move(environment(me));
			return 1;
		}
		
		if (random(kar1*4)<1){
			message_vision(HIY"$N��ǰ���һ�����ۣ����ӣ�\n"NOR,me);
			message_vision(HIR"$N�������ӣ�����һ���⣬�����߹޵������ϴ�ķ��顣\n"NOR,me);
			gold=new("/clone/money/gold");
			gold->move(environment(me));
			ob = present("wa guan", me);
                        if(ob)destruct(ob);
			return 1;
		}
		
		if (random(20)<1){
			message_vision(MAG"\n$N��ѽһ���������ϵ�ʯͷ����һ����\n"NOR,me);
			me->start_busy(random(3)+2);
			damage=me->query_skill("force",1);
			me->receive_wound("qi", random(damage/10));
		}

                
		
        return 1;        
	} else if(arg=="dochong"){
		
		me->set_temp("fresh",1);
		message_vision("$N�������������ֽ���֦��Ҷ��������ϸѰ�Ҷ�����ټ���\n",me);
		
		if (me->query("find_bug")>random(20)) {
			me->set("find_bug",0);
                                
			room = load_object(n[random(sizeof(n))]);
                        
                        message_vision("$N�������ң�����û��˿��������ټ���ֻ���뿪�������ĵط�Ѱ�ҡ�\n",me);
			message_vision("$N����ææ���뿪�ˡ�\n",me);
			me->move(room);
			message_vision("$N���˹�����\n",me);			
			return 1;
		}
		
		
		return 1;
	}	
	
}

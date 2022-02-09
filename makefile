play: libs/libEvents.so libs/libTools.so libs/libUI.so runtime/runtime_obj/main.o \
runtime/runtime_obj/Settings.o runtime/runtime_obj/GameLoop.o
	gcc -Wall -o play runtime/runtime_obj/*.o -L ./libs -lEvents -lTools -lUI

# RUNTIME DEPENDENCIES:
#	main
#	GameLoop
#	Settings

runtime/runtime_obj/main.o: runtime/main.c runtime/runtime_headers/*.h
	gcc -Wall -g -c runtime/main.c -o runtime/runtime_obj/main.o

runtime/runtime_obj/GameLoop.o: runtime/GameLoop.c runtime/runtime_headers/GameLoop.h
	gcc -Wall -g -c runtime/GameLoop.c -o runtime/runtime_obj/GameLoop.o

runtime/runtime_obj/Settings.o: runtime/Settings.c runtime/runtime_headers/Settings.h
	gcc -Wall -g -c runtime/Settings.c -o runtime/runtime_obj/Settings.o

# Object dependencies:
# 	GameEvents
# 	NumTools
# 	PlayerEvents
# 	SettingsEvents
# 	SettingsUI
# 	uiFX
# 	InputTools

clean:
	rm libs/*.so
	rm obj/*.o
	rm runtime/runtime_obj/*.o
	rm play

libs/libEvents.so: src/PlayerEvents.c libdefs/PlayerEvents.h src/SettingsEvents.c libdefs/SettingsEvents.h
	touch libs/libEvents.so
	chmod 7705 libs/libEvents.so
	gcc -Wall -fPIC -c -g src/*Events.c
	gcc -shared -o libs/libEvents.so *.o
	mv *.o obj/
	nm -D libs/libEvents.so

libs/libUI.so: src/uiFX.c src/SettingsUI.c libdefs/uiFX.h libdefs/SettingsUI.h
	touch libs/libUI.so
	chmod 7705 libs/libUI.so
	gcc -Wall -fPIC -c -g src/*UI.c src/ui*.c
	gcc -shared -o libs/libUI.so *.o
	mv *.o obj/
	nm -D libs/libUI.so

libs/libTools.so: src/*Tools.c libdefs/*Tools.h
	touch libs/libTools.so
	chmod 7705 libs/libTools.so
	gcc -Wall -fPIC -c -g src/*Tools.c
	gcc -shared -o libs/libTools.so *.o
	mv *.o obj/
	nm -D libs/libTools.so

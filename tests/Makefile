include ../Makefile

FLAGS += -fprofile-arcs -ftest-coverage
LLIB += -lcriterion -lgcov --coverage 

.PHONY: build/tests
.DEFAULT_GOAL := build/tests

build/tests: $(TESTS)/test_pixel $(TESTS)/test_resize

$(TESTS)/test_pixel: $(BUILD_TESTS)/test_pixel.o $(BUILD_TESTS)/pixel.o $(BUILD_TESTS)/cwalk.o | $(BUILD_TESTS)
	$(CC) $^ $(FLAGS) $(LLIB) -o $(TESTS)/test_pixel

$(TESTS)/test_resize: $(BUILD_TESTS)/test_resize.o $(BUILD_TESTS)/resize.o $(BUILD_TESTS)/pixel.o $(BUILD_TESTS)/cwalk.o | $(BUILD_TESTS)
	$(CC) $^ $(FLAGS) $(LLIB) -o $(TESTS)/test_resize

$(BUILD_TESTS)/test_pixel.o: $(TESTS)/test_pixel.c | $(BUILD_TESTS)
	$(CC) -c $(TESTS)/test_pixel.c $(FLAGS) -o $(BUILD_TESTS)/test_pixel.o

$(BUILD_TESTS)/test_resize.o: $(TESTS)/test_resize.c | $(BUILD_TESTS)
	$(CC) -c $(TESTS)/test_resize.c $(FLAGS) -o $(BUILD_TESTS)/test_resize.o

$(BUILD_TESTS)/pixel.o: $(SRC)/pixel.c $(INCLUDE)/pixel.h | $(BUILD_TESTS)
	$(CC) -c $(SRC)/pixel.c $(FLAGS) -o $(BUILD_TESTS)/pixel.o

$(BUILD_TESTS)/resize.o: $(SRC)/resize.c $(INCLUDE)/resize.h | $(BUILD_TESTS)
	$(CC) -c $(SRC)/resize.c $(FLAGS) -o $(BUILD_TESTS)/resize.o

$(BUILD_TESTS)/cwalk.o: $(LIBS)/cwalk.c $(LIBS)/cwalk.h | $(BUILD_TESTS)
	$(CC) -c $(LIBS)/cwalk.c $(FLAGS) -o $(BUILD_TESTS)/cwalk.o

$(BUILD_TESTS):
	mkdir -p $(BUILD_TESTS)


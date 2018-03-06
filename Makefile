.PHONY: clean All

All:
	@echo "----------Building project:[ AtomCC - Debug ]----------"
	@"$(MAKE)" -f  "AtomCC.mk"
clean:
	@echo "----------Cleaning project:[ AtomCC - Debug ]----------"
	@"$(MAKE)" -f  "AtomCC.mk" clean

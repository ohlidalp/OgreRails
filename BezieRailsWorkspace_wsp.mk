.PHONY: clean All

All:
	@echo ----------Building project:[ BezieRails - Debug ]----------
	@cd "BezieRails" && "$(MAKE)" -f "BezieRails.mk"
clean:
	@echo ----------Cleaning project:[ BezieRails - Debug ]----------
	@cd "BezieRails" && "$(MAKE)" -f "BezieRails.mk" clean

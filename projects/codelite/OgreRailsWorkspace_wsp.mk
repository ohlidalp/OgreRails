.PHONY: clean All

All:
	@echo ----------Building project:[ OgreRails - Debug ]----------
	@cd "OgreRails" && "$(MAKE)" -f "OgreRails.mk"
clean:
	@echo ----------Cleaning project:[ OgreRails - Debug ]----------
	@cd "OgreRails" && "$(MAKE)" -f "OgreRails.mk" clean

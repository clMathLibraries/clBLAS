import copy
import Common

################################################################################
# Tile Parameters
# - parameters which should match matrix system for good performance
################################################################################
class TileParameters:

  nameFormat = "%03d_%03d_%02d_%02dx%02d_%01dx%01d"

  ##############################################################################
  # Tile - constructors
  ##############################################################################
  def __init__(self):
    self.workGroupNumRows = -1
    self.workGroupNumCols = -1
    self.microTileNumRows = -1
    self.microTileNumCols = -1
    self.macroTileNumRows = -1
    self.macroTileNumCols = -1
    self.unroll           = -1

  def printAttributes(self):
    print "workGroupNumRows = %d" % self.workGroupNumRows
    print "workGroupNumCols = %d" % self.workGroupNumCols
    print "microTileNumRows = %d" % self.microTileNumRows
    print "microTileNumCols = %d" % self.microTileNumCols
    print "macroTileNumRows = %d" % self.macroTileNumRows
    print "macroTileNumCols = %d" % self.macroTileNumCols
    print "unroll           = %d" % self.unroll

  ##############################################################################
  # Tile - get Multiples
  ##############################################################################
  def getMultipleM(self):
    return (self.workGroupNumRows * self.microTileNumRows)
  def getMultipleN(self):
    return (self.workGroupNumCols * self.microTileNumCols)
  def getMultipleK(self):
    return (self.unroll)


  ##############################################################################
  # Tile - are tile parameters valid?
  ##############################################################################
  def isValid(self):
    numALoads = (self.workGroupNumRows*self.microTileNumRows*self.unroll) \
        / (self.workGroupNumRows*self.workGroupNumCols)
    numALoadsR = (self.workGroupNumRows*self.microTileNumRows*self.unroll) \
        % (self.workGroupNumRows*self.workGroupNumCols)
    numBLoads = (self.workGroupNumCols*self.microTileNumCols*self.unroll) \
        / (self.workGroupNumRows*self.workGroupNumCols)
    numBLoadsR = (self.workGroupNumCols*self.microTileNumCols*self.unroll) \
        % (self.workGroupNumRows*self.workGroupNumCols)
    if (numALoads>0 and numALoadsR>0):
      self.error = ("(%2d * %d * %d = %3d) A elements can't be loaded "
          "by (%2d * %2d = %3d) threads" ) \
          % ( self.workGroupNumRows, self.microTileNumRows, self.unroll, \
          (self.workGroupNumRows*self.microTileNumRows*self.unroll), \
          self.workGroupNumRows, self.workGroupNumCols, \
          (self.workGroupNumRows*self.workGroupNumCols) )
      return False
    elif (numBLoads>0 and numBLoadsR>0):
      self.error = ( "(%2d * %d * %d = %3d) B elements can't be loaded "
          "by (%2d * %2d = %3d) threads" ) \
          % ( self.workGroupNumCols, self.microTileNumCols, self.unroll, \
          (self.workGroupNumCols*self.microTileNumCols*self.unroll), \
          self.workGroupNumRows, self.workGroupNumCols, \
          (self.workGroupNumRows*self.workGroupNumCols) )
      return False
    else:
      return True


  ##############################################################################
  # Tile - get Name
  ##############################################################################
  def getName(self):
    return self.nameFormat \
        % ( self.macroTileNumRows, self.macroTileNumCols, self.unroll, \
        self.workGroupNumRows, self.workGroupNumCols, \
        self.microTileNumRows, self.microTileNumCols)
  def getRowName(self):
    return self.nameFormat \
        % ( 1, self.macroTileNumCols, self.unroll, \
        self.workGroupNumRows, self.workGroupNumCols, \
        self.microTileNumRows, self.microTileNumCols)
  def getColName(self):
    return self.nameFormat \
        % ( self.macroTileNumRows, 1, self.unroll, \
        self.workGroupNumRows, self.workGroupNumCols, \
        self.microTileNumRows, self.microTileNumCols)
  def getCornerName(self):
    return self.nameFormat \
        % ( 1, 1, self.unroll, \
        self.workGroupNumRows, self.workGroupNumCols, \
        self.microTileNumRows, self.microTileNumCols)

  ##############################################################################
  # Row Kernel
  # - macroTileNumRows = 1
  # - guards around gA -> lA
  # - guards around gC[gRow,:] = rC[row,:]
  ##############################################################################
  def isRowKernel(self):
    if self.workGroupNumRows * self.microTileNumRows == self.macroTileNumRows:
      return False; # normal tile kernel
    else:
      if self.macroTileNumRows == 1:
        return True; # single row kernel
      else:
        printf( ("ERROR: workGroupNumRows=%u, microTileNumRows=%u "
            "and macroTileNumRows=%u doesn't make sense\n") \
            % (self.workGroupNumRows, self.microTileNumRows, \
            self.macroTileNumRows) );
        return False; # ERROR

  ##############################################################################
  # Col Kernel
  # - macroTileNumCols = 1
  # - guards around gB -> lB
  # - guards around gC[:,gCol] = rC[:,col]
  ##############################################################################
  def isColKernel(self):
    if self.workGroupNumCols * self.microTileNumCols == self.macroTileNumCols:
      return False; # normal tile kernel
    else:
      if self.macroTileNumCols == 1:
        return True; # single row kernel
      else:
        printf(("ERROR: workGroupNumCols=%u, microTileNumCols=%u "
            "and macroTileNumCols=%u doesn't make sense\n") \
            % (self.workGroupNumCols, self.microTileNumCols, \
            self.macroTileNumCols) );
        return False; # ERROR



################################################################################
# Non Tile Parameters
# - parameters which must match matrix system for correct answer
################################################################################
class NonTileParameters:
  def __init__(self):
    self.precision = ""  # s, d, c, z
    self.order = ""      # clblasColumnMajor, clblasRowMajor
    self.transA = ""     # N, T, C
    self.transB = ""     # N, T, C
    self.beta = -1       # 0, 1

  def printAttributes(self):
    print "precision = " + self.precision
    print "order     = " + self.order
    print "transA    = " + self.transA
    print "transB    = " + self.transB
    print "beta      = %d" % self.beta

  ##############################################################################
  # NonTile - get Name
  ##############################################################################
  def getName(self):
    return "%sgemm_%3s_%1s%1s_B%d" \
        % (Common.hostDataChar[self.precision], \
        "Col" if self.order=="clblasColumnMajor" else "Row", \
        self.transA, self.transB, self.beta )



################################################################################
# Kernel Parameters
################################################################################
class KernelParameters( NonTileParameters, TileParameters ):

  ##############################################################################
  # Kernel - constructor
  ##############################################################################
  def __init__(self):
    NonTileParameters.__init__(self)
    TileParameters.__init__(self)
    self.localRowPad = 0
    self.localColPad = 0

  ##############################################################################
  # Kernel - use tile
  ##############################################################################
  def useTile(self, tile):
    self.workGroupNumRows = tile.workGroupNumRows
    self.workGroupNumCols = tile.workGroupNumCols
    self.microTileNumRows = tile.microTileNumRows
    self.microTileNumCols = tile.microTileNumCols
    self.macroTileNumRows = tile.macroTileNumRows
    self.macroTileNumCols = tile.macroTileNumCols
    self.unroll           = tile.unroll

  def printAttributes(self):
    NonTileParameters.printAttributes(self)
    TileParameters.printAttributes(self)

  ##############################################################################
  # Kernel - get Name
  ##############################################################################
  def getName(self):
    return NonTileParameters.getName(self) \
        + "_" + TileParameters.getName(self)
  def getRowName(self):
    return NonTileParameters.getName(self) \
        + "_" + TileParameters.getRowName(self)
  def getColName(self):
    return NonTileParameters.getName(self) \
        + "_" + TileParameters.getColName(self)
  def getCornerName(self):
    return NonTileParameters.getName(self) \
        + "_" + TileParameters.getCornerName(self)

